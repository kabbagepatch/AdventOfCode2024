#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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

  sort(leftList.begin(), leftList.end());
  sort(rightList.begin(), rightList.end());

  int distance = 0;
  for (int i = 0; i < leftList.size(); i += 1) {
    distance += abs(leftList[i] - rightList[i]);
  }

  cout << distance << '\n';

  myfile.close();
}
