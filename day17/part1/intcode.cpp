#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

vector<int> split(string s, string delimiter) {
  vector<int> results;
  size_t pos = 0;
  string token;
  while ((pos = s.find(delimiter)) != string::npos) {
      token = s.substr(0, pos);
      results.push_back(stoi(token));
      s.erase(0, pos + delimiter.length());
  }
  results.push_back(stoi(s));
  return results;
}

bool isNumber(char c) {
  return c >= '0' && c <= '9';
}

void print(auto stuff) {
  cout << stuff << endl;
}

void print(vector<int> stuff) {
  for (int t : stuff) {
    cout << t << endl;
  }
  cout << endl;
  cout << endl;
}

int main () {
  ifstream myfile;
  myfile.open ("../input");
  vector<string> lines;
  if (myfile.is_open()) {
    string line_string;
    while(getline(myfile, line_string)) {
      lines.push_back(line_string);
    }
  }
  myfile.close();

  string register_prefix = "Register X: ";
  string program_prefix = "Program: ";

  long A = stol(lines[0].substr(register_prefix.size()));
  long B = stol(lines[1].substr(register_prefix.size()));
  long C = stol(lines[2].substr(register_prefix.size()));

  vector<int> program = split(lines[4].substr(program_prefix.size()), ",");

  for (int i = 0; i < program.size(); i += 2) {
    int opcode = program[i];
    int operand = program[i + 1];
    long combo_operand = operand;
    switch(operand) {
      case 4: combo_operand = A; break;
      case 5: combo_operand = B; break;
      case 6: combo_operand = C; break;
    }

    switch(opcode) {
      case 0:
        A = A / pow(2, combo_operand);
        break;
      case 1:
        B = B ^ operand;
        break;
      case 2:
        B = combo_operand % 8;
        break;
      case 3:
        if (A != 0) {
          i = operand - 2;
        }
        break;
      case 4:
        B = B ^ C;
        break;
      case 5:
        cout << combo_operand % 8 << ",";
        cout << "REGISTERS: " << A << " " << B << " " << C << " " << endl;
        break;
      case 6:
        B = A / pow(2, combo_operand);
        break;
      case 7:
        C = A / pow(2, combo_operand);
        break;
    }
  }
  
  cout << endl;
}
