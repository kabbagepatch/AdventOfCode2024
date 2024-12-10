#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

void print(vector<string> stuff) {
  for (string t : stuff) {
    cout << t << endl;
  }
  cout << endl;
  cout << endl;
}

int get_score(vector<string>& trail_map, map<string, int>& scores, pair<int, int> start) {
  int r = start.first;
  int c = start.second;
  string key = to_string(start.first) + "_" + to_string(start.second);
  int cur_space = trail_map[r][c] - '0';
  if (cur_space == 9) {
    scores[key] = 1;
    return 1;
  }

  if (scores.find(key) != scores.end()) {
    return scores[key];
  }

  int score = 0;
  if (r > 0 && trail_map[r - 1][c] - '0' == cur_space + 1) {
    score += get_score(trail_map, scores, make_pair(r - 1, c));
  }
  if (r < trail_map.size() - 1 && trail_map[r + 1][c] - '0' == cur_space + 1) {
    score += get_score(trail_map, scores, make_pair(r + 1, c));
  }
  if (c > 0 && trail_map[r][c - 1] - '0' == cur_space + 1) {
    score += get_score(trail_map, scores, make_pair(r, c - 1));
  }
  if (c < trail_map[0].size() - 1 && trail_map[r][c + 1] - '0' == cur_space + 1) {
    score += get_score(trail_map, scores, make_pair(r, c + 1));
  }

  scores[key] = score;
  return score;
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

  int score = 0;
  for (int i = 0; i < lines.size(); i += 1) {
    for (int j = 0; j < lines[0].size(); j += 1) {
      if (lines[i][j] == '0') {
        map<string, int> scores;
        score += get_score(lines, scores, make_pair(i, j));
      }
    }
  }

  cout << score << endl;
}
