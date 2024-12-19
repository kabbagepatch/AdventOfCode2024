#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
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

void print(string stuff) {
  cout << stuff << endl;
}

void print(vector<string> stuff) {
  for (string t : stuff) {
    cout << t << endl;
  }
  cout << endl;
  cout << endl;
}

bool is_design_possible(string design, vector<string>& towels, map<string, bool>& possible_designs) {
  if (design.empty()) return true;

  if (possible_designs.find(design) != possible_designs.end()) {
    return possible_designs[design];
  }

  for (string towel : towels) {
    if (design == towel) {
      possible_designs[design] = true;
      return true;
    }

    int towel_ind = design.find(towel);
    if (towel_ind != 0) {
      continue;
    }

    bool is_rest_possible = is_design_possible(design.substr(towel.length()), towels, possible_designs);
    if (is_rest_possible) {
      possible_designs[design] = true;
      return true;
    }
  }

  possible_designs[design] = false;
  return false;
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

  vector<string> towels = split(lines[0], ", ");

  int possible_designs_count = 0;
  map<string, bool> possible_designs;
  for (int i = 2; i < lines.size(); i += 1) {
    if (is_design_possible(lines[i], towels, possible_designs)) {
      possible_designs_count += 1;
    }
  }

  cout << possible_designs_count << endl;
}
