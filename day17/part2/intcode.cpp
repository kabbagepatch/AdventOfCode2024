#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
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



long get_A_values(vector<long>& As, long A, vector<int>& Bs, int Bind) {
  int B = Bs[Bind];
  if (Bind == -1) {
    As.push_back(A);
    return -1;
  }
  A = A * 8;

  vector<long> possibleNextBs;
  for (long i = 7; i >= 0; i -= 1) {
    long C = (A + (i ^ 2)) / (1 << i);
    if (B == ((i ^ C) ^ 7) % 8) {
      possibleNextBs.push_back(i);
    }
  }
  if (possibleNextBs.size() == 0) {
    return -1;
  }

  for (long i : possibleNextBs) {
    long nextA = get_A_values(As, A + (i ^ 2), Bs, Bind - 1);
    if (nextA != -1) {
      return nextA;
    }
  }
  
  return -1;
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

  string program_string = lines[4].substr(program_prefix.size());
  vector<int> program = split(program_string, ",");
  
  vector<long> As;
  get_A_values(As, 0, program, program.size() - 1);
  cout << *min_element(As.begin(), As.end()) << endl;
}
