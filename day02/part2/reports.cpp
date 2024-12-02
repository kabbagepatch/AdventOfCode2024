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

bool isSafe(vector<int>& levels, int indexToIgnore=-1) {
  bool isIncreasing = levels[0] < levels[1];
  if (indexToIgnore == 0) {
    isIncreasing = levels[1] < levels[2];
  } else if (indexToIgnore == 1) {
    isIncreasing = levels[0] < levels[2];
  }
  for (int i = 0; i < levels.size() - 1; i += 1) {
    int cur = i;
    int next = i + 1;
    if (indexToIgnore == i) {
      i += 1;
      cur = i;
      next = i + 1;
    } else if (indexToIgnore == i + 1) {
      next += 1;
    }
    if (next >= levels.size()) {
      break;
    }
    if (
      abs(levels[cur] - levels[next]) < 1
      || abs(levels[cur] - levels[next]) > 3
      || (isIncreasing && levels[cur] > levels[next])
      || (!isIncreasing && levels[cur] < levels[next])
    ) {
      return false;
    }
  }

  return true;
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
    for (int i = -1; i < (int)levels.size(); i += 1) {
      if (isSafe(levels, i)) {
        nSafe += 1;
        break;
      }
    }
  }

  cout << nSafe << endl;
}
