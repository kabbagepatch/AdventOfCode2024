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

  regex pattern("mul\\((\\d+),(\\d+)\\)");
  int sum = 0;
  
  for (string line : lines) {
    sregex_iterator currentMatch(line.begin(), line.end(), pattern);
    sregex_iterator end;
    while (currentMatch != end) {
      smatch match = *currentMatch;
      sum += stoi(match[1]) * stoi(match[2]);
      ++currentMatch;
    }
  }

  cout << sum << endl;
}
