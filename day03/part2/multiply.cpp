#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

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

  regex mulPattern("mul\\((\\d+),(\\d+)\\)");
  regex doDontPattern("do\\(\\)(.*?)don't\\(\\)");
  int sum = 0;

  string fullLine = "do()";
  for (string line : lines) {
    fullLine += line;
  }
  fullLine += "don't()";

  sregex_iterator currentDoDontMatch(fullLine.begin(), fullLine.end(), doDontPattern);
  sregex_iterator end;
  while (currentDoDontMatch != end) {
    smatch doDontMatch = *currentDoDontMatch;
    string doDontString = doDontMatch[1].str();
    sregex_iterator currentMulMatch(doDontString.begin(), doDontString.end(), mulPattern);
    while (currentMulMatch != end) {
      smatch match = *currentMulMatch;
      string mulNum1 = match[1];
      string mulNum2 = match[2];
      sum += stoi(mulNum1) * stoi(mulNum2);
      ++currentMulMatch;
    }
    ++currentDoDontMatch;
  }

  cout << sum << endl;
}

