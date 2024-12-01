#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

vector<string> split(string s, string delimiter) {
  vector<string> results;
  size_t pos = 0;
  string token;
  while ((pos = s.find(delimiter)) != string::npos) {
      token = s.substr(0, pos);
      results.push_back(token);
      s.erase(0, pos + delimiter.length());
  }
  results.push_back(s);
  return results;
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

  vector<int> leftList;
  vector<int> rightList;

  for (string line : lines) {
    vector<string> locations = split(line, "   ");
    leftList.push_back(stoi(locations[0]));
    rightList.push_back(stoi(locations[1]));
  }

  map<int, int> nOccurances;
  for (int i = 0; i < rightList.size(); i += 1) {
    if (nOccurances.find(rightList[i]) != nOccurances.end()) {
      nOccurances[rightList[i]] += 1;
    } else {
      nOccurances[rightList[i]] = 1;
    }
  }

  int totalScore = 0;
  map<int, int> scores;
  for (int i = 0; i < leftList.size(); i += 1) {
    if (scores.find(leftList[i]) != scores.end()) {
      totalScore += scores[leftList[i]];
    } else {
      if (nOccurances.find(rightList[i]) != nOccurances.end()) {
        int score = leftList[i] * nOccurances[leftList[i]];
        totalScore += score;
        scores[leftList[i]] = score;
      }
    }
  }

  cout << totalScore << '\n';

  myfile.close();
}
