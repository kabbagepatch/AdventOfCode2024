#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

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
  vector<vector<string>> keys;
  vector<vector<string>> locks;
  int i = 0;
  bool key = false;
  vector<string> cur_schematic;
  if (myfile.is_open()) {
    string line_string;
    while(getline(myfile, line_string)) {
      lines.push_back(line_string);
      if (i % 8 == 0) {
        key = line_string[0] == '.';
      }
      i += 1;

      if (line_string.empty()) {
        if (key) keys.push_back(cur_schematic);
        else locks.push_back(cur_schematic);

        cur_schematic.clear();
        continue;
      }

      cur_schematic.push_back(line_string);
    }
    if (key) keys.push_back(cur_schematic);
    else locks.push_back(cur_schematic);
  }
  myfile.close();

  int n_overlaps = 0;
  int n_fits = 0;
  for (vector<string> key : keys) {
    for (vector<string> lock : locks) {
      bool overlap = false;
      for (int i = 0; i < key.size(); i += 1) {
        for (int j = 0; j < key[0].size(); j += 1) {
          if (key[i][j] == '#' && lock[i][j] == '#') {
            n_overlaps += 1;
            overlap = true;
            break;
          }
        }
        if (overlap) break;
      }
      if (!overlap) n_fits += 1;
    }
  }

  cout << n_fits << endl;
}
