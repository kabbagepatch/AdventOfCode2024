#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
using namespace std;

void print(vector<string> stuff) {
  for (string t : stuff) {
    cout << t << endl;
  }
  cout << endl;
  cout << endl;
}

bool get_gate_result(string gate, map<string, bool>& gates, map<string, string>& operations) {
  if (gates.find(gate) != gates.end()) {
    return gates[gate];
  }

  regex pattern("(.*) (AND|OR|XOR) (.*)");
  smatch matches;
  regex_search(operations[gate], matches, pattern);
  string left_operand = matches[1];
  string operation = matches[2];
  string right_operand = matches[3];

  bool left_operand_value = get_gate_result(left_operand, gates, operations);
  bool right_operand_value = get_gate_result(right_operand, gates, operations);

  if (operation == "AND") return left_operand_value && right_operand_value;
  if (operation == "OR") return left_operand_value || right_operand_value;
  return left_operand_value ^ right_operand_value;
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

  map<string, bool> gates;
  map<string, string> operations;
  regex operation_pattern("(.*) -> (.*)");
  int z_gates = 0;
  bool reading_gates = true;
  for (string line : lines) {
    if (line.empty()) {
      reading_gates = false;
      continue;
    }

    if (reading_gates) {
      gates[line.substr(0, 3)] = line[5] == '1';
    } else {
      smatch matches;
      regex_search(line, matches, operation_pattern);
      string operation = matches[1];
      string result = matches[2];
      operations[result] = operation;
      if (result[0] == 'z') z_gates += 1;
    } 
  }

  string number = "";
  for (int i = 0; i < z_gates; i += 1) {
    string gate = "z";
    if (i < 10) gate += "0";
    gate += to_string(i);

    bool result = get_gate_result(gate, gates, operations);
    gates[gate] = result;
    number = to_string(gates[gate]) + number;
  }

  cout << stol(number, nullptr, 2) << endl;
}
