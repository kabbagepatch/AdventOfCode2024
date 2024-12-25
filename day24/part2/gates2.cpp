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

struct gate {
  string type;
  string left_operand;
  string right_operand;
  string output;
};

struct adder_step {
  gate xor1 = {"XOR"};
  gate xor2 = {"XOR"};
  gate and1 = {"AND"};
  gate and2 = {"AND"};
  gate or1 = {"OR"};
};

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
      string output = matches[2];
      operations[output] = operation;
      if (output[0] == 'z') z_gates += 1;
    } 
  }

  regex operand_pattern("(.*) (AND|OR|XOR) (.*)");
  vector<adder_step> adder_steps(z_gates - 1);
  for (pair<string, string> operation : operations) {
    string output = operation.first;
    string operands = operation.second;\
    smatch matches;
    regex_search(operands, matches, operand_pattern);
    string left_operand = matches[1];
    string operation_type = matches[2];
    string right_operand = matches[3];
    if (operands[0] == 'x' || operands[0] == 'y') {
      int step_index = stoi(operands.substr(1, 2));

      if (operation_type == "XOR") {
        adder_steps[step_index].xor1.left_operand = left_operand;
        adder_steps[step_index].xor1.right_operand = right_operand;
        adder_steps[step_index].xor1.output = output;
      } else if (operation_type == "AND") {
        adder_steps[step_index].and1.left_operand = left_operand;
        adder_steps[step_index].and1.right_operand = right_operand;
        adder_steps[step_index].and1.output = output;
      }
    }
    if (output[0] == 'z') {
      int step_index = stoi(output.substr(1, 2));

      if (operation_type == "XOR") {
        adder_steps[step_index].xor2.left_operand = left_operand;
        adder_steps[step_index].xor2.right_operand = right_operand;
        adder_steps[step_index].xor2.output = output;
      }
    }
  }

  for (pair<string, string> operation : operations) {
    string output = operation.first;
    string operands = operation.second;
    if (operands[0] == 'x' || operands[0] == 'y') continue;

    smatch matches;
    regex_search(operands, matches, operand_pattern);
    string left_operand = matches[1];
    string operation_type = matches[2];
    string right_operand = matches[3];
    bool found = false;
    if (operation_type == "OR") {
      for (int i = 1; i < adder_steps.size(); i += 1) {
        if (
          adder_steps[i].and1.output == left_operand
          || adder_steps[i].and1.output == right_operand
          || adder_steps[i].and2.output == left_operand
          || adder_steps[i].and2.output == right_operand
        ) {
          adder_steps[i].or1.left_operand = left_operand;
          adder_steps[i].or1.right_operand = right_operand;
          adder_steps[i].or1.output = output;
          break;
        }
      }
    } else if (operation_type == "AND") {
      bool found = false;
      for (int i = 1; i < adder_steps.size(); i += 1) {
        if (
          adder_steps[i].xor1.output == left_operand
          || adder_steps[i].xor1.output == right_operand
          || adder_steps[i - 1].or1.output == left_operand
          || adder_steps[i - 1].or1.output == right_operand
        ) {
          adder_steps[i].and2.left_operand = left_operand;
          adder_steps[i].and2.right_operand = right_operand;
          adder_steps[i].and2.output = output;
          break;
        }
      }
    } else if (operation_type == "XOR") {
      bool found = false;
      for (int i = 1; i < adder_steps.size(); i += 1) {
        if (adder_steps[i].xor1.output == left_operand || adder_steps[i].xor1.output == right_operand) {
          adder_steps[i].xor2.left_operand = left_operand;
          adder_steps[i].xor2.right_operand = right_operand;
          adder_steps[i].xor2.output = output;
          break;
        }
      }
    }
  }

  for (pair<string, string> operation : operations) {
    string output = operation.first;
    string operands = operation.second;
    smatch matches;
    regex_search(operands, matches, operand_pattern);
    string left_operand = matches[1];
    string operation_type = matches[2];
    string right_operand = matches[3];
    if (operation_type == "OR") {
      bool found = false;
      for (int i = 0; i < adder_steps.size(); i += 1) {
        if (
          adder_steps[i].and1.output == left_operand
          || adder_steps[i].and1.output == right_operand
          || adder_steps[i].and2.output == left_operand
          || adder_steps[i].and2.output == right_operand
        ) {
          if (adder_steps[i].or1.left_operand.empty()) {
            adder_steps[i].or1.left_operand = left_operand;
            adder_steps[i].or1.right_operand = right_operand;
            adder_steps[i].or1.output = output;
          }
          break;
        }
      }
    }
  }

  cout << endl;

  for (int i = 2; i < adder_steps.size() - 1; i += 1) {
    adder_step step = adder_steps[i];
    adder_step previos_step = adder_steps[i - 1];

    if (step.xor2.output[0] != 'z') {
      cout << "XOR2 output is not an output for step " << i << endl;
      cout << step.xor2.output << endl;
      if (step.xor1.output[0] == 'z') {
        cout << step.xor1.output << endl;
      } else if (step.and1.output[0] == 'z') {
        cout << step.and1.output << endl;
      } else if (step.and2.output[0] == 'z') {
        cout << step.and2.output << endl;
      } else if (step.or1.output[0] == 'z') {
        cout << step.or1.output << endl;
      }
      continue;
    }

    if (step.xor2.left_operand != step.xor1.output && step.xor2.right_operand != step.xor1.output) {
      cout << "XOR1 output not XOR2 input for step " << i << endl;
      cout << step.xor1.output << endl;
    }

    if (step.or1.left_operand != step.and1.output && step.or1.right_operand != step.and1.output) {
      cout << "AND1 output not OR input for step " << i << endl;
      cout << step.and1.output << endl;
    }
    if (step.or1.left_operand != step.and2.output && step.or1.right_operand != step.and2.output) {
      cout << "AND2 output not OR input for step " << i << endl;
      cout << step.and2.output << endl;
    }
  }
}
