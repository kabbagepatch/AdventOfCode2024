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

string add_binary(const string &a, const string &b) {
  string result = "";
  int i = a.size() - 1, j = b.size() - 1, carry = 0;

  while (i >= 0 || j >= 0 || carry) {
    int sum = carry;
    if (i >= 0) sum += a[i--] - '0';
    if (j >= 0) sum += b[j--] - '0';

    carry = sum / 2;
    result += (sum % 2) + '0';
  }

  reverse(result.begin(), result.end());
  return result;
}

bool get_gate_result(string gate, set<string>& gates_involved, map<string, bool>& input_gates, map<string, bool>& gate_results, map<string, string>& operations) {
  if (gate[0] == 'x' || gate[0] == 'y') {
    return input_gates[gate];
  }
  if (gate_results.find(gate) != gate_results.end()) {
    return gate_results[gate];
  }

  regex pattern("(.*) (AND|OR|XOR) (.*)");
  smatch matches;
  regex_search(operations[gate], matches, pattern);
  string left_operand = matches[1];
  string operation = matches[2];
  string right_operand = matches[3];

  if (left_operand[0] != 'x' && left_operand[0] != 'y') gates_involved.insert(left_operand);
  if (right_operand[0] != 'x' && right_operand[0] != 'y') gates_involved.insert(right_operand);

  bool left_operand_value = get_gate_result(left_operand, gates_involved, input_gates, gate_results, operations);
  bool right_operand_value = get_gate_result(right_operand, gates_involved, input_gates, gate_results, operations);

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

  for (int carry_ind = 37; carry_ind < 38; carry_ind += 1) {
    for (int i = 0; i < z_gates - 1; i += 1) {
      string x_gate = i < 10 ? "x0" + to_string(i) : "x" + to_string(i);
      if (i == carry_ind) input_gates[x_gate] = 1;
      else input_gates[x_gate] = 1;

      string y_gate = i < 10 ? "y0" + to_string(i) : "y" + to_string(i);
      if (i == carry_ind) input_gates[y_gate] = 1;
      else input_gates[y_gate] = 1;
    }

    string x_number = "";
    for (int i = 0; i < z_gates - 1; i += 1) {
      string gate = i < 10 ? "x0" + to_string(i) : "x" + to_string(i);
      x_number = to_string(input_gates[gate]) + x_number;
    }

    string y_number = "";
    for (int i = 0; i < z_gates - 1; i += 1) {
      string gate = i < 10 ? "y0" + to_string(i) : "y" + to_string(i);
      y_number = to_string(input_gates[gate]) + y_number;
    }

    string z_number = "";
    map<string, bool> gate_results;
    map<string, set<string>> gate_inputs;
    for (int i = 0; i < z_gates; i += 1) {
      string gate = i < 10 ? "z0" + to_string(i) : "z" + to_string(i);
      set<string> gates_involved;
      bool result = get_gate_result(gate, gates_involved, input_gates, gate_results, operations);
      gate_results[gate] = result;
      gate_inputs[gate] = gates_involved;
      z_number = to_string(gate_results[gate]) + z_number;
    }

    string actual_z_number = add_binary(x_number, y_number);
    cout << "x =  " << x_number << endl;
    cout << "y =  " << y_number << endl;
    cout << "z = " << actual_z_number << endl;
    cout << "Z = " << z_number << endl;

    vector<int> incorrect_indices;
    for (int i = 0; i < z_number.length(); i += 1) {
      if (actual_z_number[z_number.length() - i - 1] != z_number[z_number.length() - i - 1]) {
        cout << i << " ";
        incorrect_indices.push_back(i);
      }
    }
    cout << endl;
    cout << endl;
  }

  // while (!incorrect_indices.empty()) {
  //   int first_incorrect_index = incorrect_indices[0];
  //   set<string> correct_outputs;
  //   for (int i = 0; i < first_incorrect_index; i += 1) {
  //     string gate = i < 10 ? "z0" + to_string(i) : "z" + to_string(i);
  //     correct_outputs.insert(gate_inputs[gate].begin(), gate_inputs[gate].end());
  //   }

  //   vector<string> incorrect_outputs;
  //   string gate = "z" + to_string(first_incorrect_index);
  //   set_difference(gate_inputs[gate].begin(), gate_inputs[gate].end(), correct_outputs.begin(), correct_outputs.end(), back_inserter(incorrect_outputs));

  //   bool done = false;
  //   for (int i = 0; i < incorrect_outputs.size() - 1; i += 1) {
  //     string i_operation = operations[incorrect_outputs[i]];
      
  //     for (int j = i + 1; j < incorrect_outputs.size(); j += 1) {
  //       if (j == 5) continue;

  //       string j_operation = operations[incorrect_outputs[j]];
  //       cout << "i = " << i << ": " << incorrect_outputs[i] << " = " << i_operation << endl;
  //       cout << "j = " << j << ": " << incorrect_outputs[j] << " = " << j_operation << endl;

  //       operations[incorrect_outputs[j]] = i_operation;
  //       operations[incorrect_outputs[i]] = j_operation;
  //       gate_inputs.clear();
  //       gate_results.clear();
  //       incorrect_indices.clear();

  //       z_number = "";
  //       for (int g = 0; g < z_gates; g += 1) {
  //         string gate = g < 10 ? "z0" + to_string(g) : "z" + to_string(g);
  //         set<string> gates_involved;
  //         bool result = get_gate_result(gate, gates_involved, input_gates, gate_results, operations);
  //         gate_results[gate] = result;
  //         gate_inputs[gate] = gates_involved;
  //         z_number = to_string(gate_results[gate]) + z_number;
  //       }

  //       for (int g = 0; g < z_number.length(); g += 1) {
  //         if (actual_z_number[z_number.length() - g - 1] != z_number[z_number.length() - g - 1]) {
  //           cout << g << " ";
  //           incorrect_indices.push_back(g);
  //         }
  //       }
  //       cout << endl;
  //       cout << endl;

  //       if (incorrect_indices[0] != first_incorrect_index) {
  //         cout << incorrect_outputs[i] << ", " << incorrect_outputs[j] << endl;
  //         done = true;
  //         break;
  //       }

  //       operations[incorrect_outputs[i]] = i_operation;
  //       operations[incorrect_outputs[j]] = j_operation;
  //     }
  //     if (done) break;
  //   }
  // }
}
