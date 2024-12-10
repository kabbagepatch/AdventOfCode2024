#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

void print(vector<string> stuff) {
  for (string t : stuff) {
    cout << t << endl;
  }
  cout << endl;
  cout << endl;
}

set<pair<int, int>> get_peaks_visited(vector<string>& trail_map, map<string, set<pair<int, int>>>& peaks_reached, pair<int, int> start) {
  int r = start.first;
  int c = start.second;
  string key = to_string(start.first) + "_" + to_string(start.second);
  set<pair<int, int>> peaks_visited;
  int cur_space = trail_map[r][c] - '0';
  if (cur_space == 9) {
    peaks_visited.insert(start);
    peaks_reached[key] = peaks_visited;
    return peaks_visited;
  }

  if (peaks_reached.find(key) != peaks_reached.end()) {
    return peaks_reached[key];
  }

  vector<pair<int, int>> next_coords;
  if (r > 0 && trail_map[r - 1][c] - '0' == cur_space + 1) {
    next_coords.push_back(make_pair(r - 1, c));
  }
  if (r < trail_map.size() - 1 && trail_map[r + 1][c] - '0' == cur_space + 1) {
    next_coords.push_back(make_pair(r + 1, c));
  }
  if (c > 0 && trail_map[r][c - 1] - '0' == cur_space + 1) {
    next_coords.push_back(make_pair(r, c - 1));
  }
  if (c < trail_map[0].size() - 1 && trail_map[r][c + 1] - '0' == cur_space + 1) {
    next_coords.push_back(make_pair(r, c + 1));
  }

  for (pair<int, int> coord : next_coords) {
    set<pair<int, int>> peaks = get_peaks_visited(trail_map, peaks_reached, coord);
    for (pair <int, int> peak : peaks) {
      peaks_visited.insert(peak);
    }
  }

  peaks_reached[key] = peaks_visited;
  return peaks_visited;
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
        map<string, set<pair<int, int>>> peaks_reached;
        set<pair<int, int>> peaks = get_peaks_visited(lines, peaks_reached, make_pair(i, j));
        score += peaks.size();
      }
    }
  }

  cout << score << endl;
}
