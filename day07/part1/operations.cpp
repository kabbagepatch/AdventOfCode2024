#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
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

bool isResultPossible(string operandString, long result) {
  if (operandString.empty()) {
    return true;
  }

  vector<int> operands = split(operandString, " ");
  if (operands.size() == 1) {
    return operands[0] == result;
  }

  long lastOperand = operands[operands.size() - 1];
  string newOperandString = operandString.substr(0, operandString.length() - to_string(lastOperand).length() - 1);

  bool addition = false;
  if (result - lastOperand > 0) {
    addition = isResultPossible(newOperandString, result - lastOperand);
  }

  bool multiplication = false;
  if (result % lastOperand == 0) {
    multiplication = isResultPossible(newOperandString, result / lastOperand);
  }

  return addition || multiplication;
}

int main () {
  ifstream myfile;
  myfile.open ("../input");
  vector<string> lines;
  if (myfile.is_open()) {
    string lineString;
    while(getline(myfile, lineString)) {
      lines.push_back(lineString);
    }
  }
  myfile.close();

  long sum = 0;
  for (string line : lines) {
    int colonIndex = line.find(':');
    long result = stol(line.substr(0, colonIndex));
    string operandString = line.substr(colonIndex + 2);
    if (isResultPossible(operandString, result)) {
      sum += result;
    }
  }

  cout << sum << endl;
}
