#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

void print(vector<string> stuff) {
  for (string t : stuff) {
    cout << t << endl;
  }
  cout << endl;
  cout << endl;
}

string get_gate_expression(string gate, map<string, bool>& input_gates, map<string, string>& gate_expressions, map<string, string>& operations) {
  if (gate[0] == 'x' || gate[0] == 'y') {
    return gate;
  }
  string gate_operation = operations[gate];
  if (gate_operation[0] == 'x' || gate_operation[0] == 'y') {
    gate_expressions[gate] = gate_operation;
    return gate_operation;
  }

  if (gate_expressions.find(gate) != gate_expressions.end()) {
    return gate_expressions[gate];
  }

  regex pattern("(.*) (AND|OR|XOR) (.*)");
  smatch matches;
  regex_search(operations[gate], matches, pattern);
  string left_operand = matches[1];
  string operation = matches[2];
  string right_operand = matches[3];

  string left_operand_expression = get_gate_expression(left_operand, input_gates, gate_expressions, operations);
  string right_operand_expression = get_gate_expression(right_operand, input_gates, gate_expressions, operations);

  return "(" + left_operand_expression + ") " + operation + " (" + right_operand_expression + ")";
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

  map<string, bool> input_gates;
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
      input_gates[line.substr(0, 3)] = line[5] == '1';
    } else {
      smatch matches;
      regex_search(line, matches, operation_pattern);
      string operation = matches[1];
      string result = matches[2];
      operations[result] = operation;
      if (result[0] == 'z') z_gates += 1;
    } 
  }

  map<string, string> gate_expressions;
  for (int i = 0; i < z_gates; i += 1) {
    string gate = i < 10 ? "z0" + to_string(i) : "z" + to_string(i);
    string result = get_gate_expression(gate, input_gates, gate_expressions, operations);
    gate_expressions[gate] = result;
  }

  cout << gate_expressions["z14"] << endl;
  cout << gate_expressions["z16"] << endl;
}
