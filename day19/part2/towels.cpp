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

long get_design_arrangement_count(string design, vector<string>& towels, map<string, long>& design_arrangement_counts) {
  if (design.empty()) return 0;

  if (design_arrangement_counts.find(design) != design_arrangement_counts.end()) {
    return design_arrangement_counts[design];
  }

  long design_arrangement_count = 0;
  for (string towel : towels) {
    if (design == towel) {
      design_arrangement_count += 1;
      continue;
    }

    int towel_ind = design.find(towel);
    if (towel_ind != 0) {
      continue;
    }

    design_arrangement_count += get_design_arrangement_count(design.substr(towel.length()), towels, design_arrangement_counts);
  }

  design_arrangement_counts[design] = design_arrangement_count;
  return design_arrangement_count;
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

  long total_count = 0;
  map<string, long> design_arrangement_counts;
  for (int i = 2; i < lines.size(); i += 1) {
    long count = get_design_arrangement_count(lines[i], towels, design_arrangement_counts);
    total_count += count;
  }

  cout << total_count << endl;
}
