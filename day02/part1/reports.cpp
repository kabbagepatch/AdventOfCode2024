#include <iostream>
#include <fstream>
#include <string>
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

void print(vector<string> stuff) {
  for (string t : stuff) {
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
    string lineString;
    while(getline(myfile, lineString)) {
      lines.push_back(lineString);
    }
  }
  myfile.close();

  int nSafe = 0;
  for (string line: lines) {
    vector<int> levels = split(line, " ");
    bool isIncreasing = levels[0] < levels[1];
    bool isSafe = true;
    for (int i = 0; i < levels.size() - 1; i += 1) {
      if (
        abs(levels[i] - levels[i + 1]) < 1
        || abs(levels[i] - levels[i + 1]) > 3
        || (isIncreasing && levels[i] > levels[i + 1])
        || (!isIncreasing && levels[i] < levels[i + 1])
      ) {
        isSafe = false;
        break;
      }
    }
    if (isSafe) {
      nSafe += 1;
    }
  }

  cout << nSafe << endl;
}
