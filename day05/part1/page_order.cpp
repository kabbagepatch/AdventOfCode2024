#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
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
  int nRules = -1;
  bool readingRules = true;
  if (myfile.is_open()) {
    string lineString;
    while(getline(myfile, lineString)) {
      if (lineString.empty()) readingRules = false;
      if (readingRules) nRules += 1;
      lines.push_back(lineString);
    }
  }
  myfile.close();

  map<int, vector<int>> orderRules;
  for (int i = 0; i <= nRules; i += 1) {
    int leftNumber = stoi(lines[i].substr(0, 2));
    int rightNumber = stoi(lines[i].substr(3, 2));

    if (orderRules.find(leftNumber) == orderRules.end()) {
      orderRules[leftNumber] = vector<int>();
    }

    orderRules[leftNumber].push_back(rightNumber);
  }

  int middlePageSum = 0;
  for (int i = nRules + 2; i < lines.size(); i += 1) {
    vector<int> pages = split(lines[i], ",");
    bool isInOrder = true;
    for (int i = 0; i < pages.size(); i += 1) {
      int curPage = pages[i];
      for (int j = i + 1; j < pages.size(); j += 1) {
        int nextPage = pages[j];
        if (find(orderRules[nextPage].begin(), orderRules[nextPage].end(), curPage) != orderRules[nextPage].end()) {
          isInOrder = false;
          break;
        }
      }
      if (!isInOrder) break;
    }

    if (isInOrder) {
      middlePageSum += pages[pages.size() / 2];
    }
  }

  cout << middlePageSum << endl;
}
