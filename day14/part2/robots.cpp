#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

const int MAP_WIDTH = 101;
const int MAP_HEIGHT = 103;
const int TIME = 10000;

void print(vector<string> stuff) {
  for (string t : stuff) {
    cout << t << endl;
  }
  cout << endl;
  cout << endl;
}

void print(vector<int> stuff) {
  for (int t : stuff) {
    if (t > 10) cout << t << " ";
  }
  cout << endl;
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

  vector<pair<int, int>> robot_positions;
  vector<pair<int, int>> robot_velocities;
  vector<string> area_map(MAP_HEIGHT);
  for (int i = 0; i < MAP_HEIGHT; i += 1) {
    area_map[i] = string(MAP_WIDTH, '.');
  }

  regex pattern("p=(\\d+),(\\d+) v=(-?\\d+),(-?\\d+)");
  for (string line : lines) {
    smatch matches;
    regex_search(line, matches, pattern);
    int px = stoi(matches[1]);
    int py = stoi(matches[2]);
    robot_positions.push_back(make_pair(px, py));
    area_map[px][py] = '#';

    int vx = stoi(matches[3]);
    int vy = stoi(matches[4]);
    robot_velocities.push_back(make_pair(vx, vy));
  }

  for (int i = 1; i <= TIME; i += 1) {
    for (int r = 0; r < robot_positions.size(); r += 1) {
      int px = robot_positions[r].first;
      int py = robot_positions[r].second;
      int vx = robot_velocities[r].first;
      int vy = robot_velocities[r].second;
      robot_positions[r].first = (MAP_WIDTH + (px + vx) % MAP_WIDTH) % MAP_WIDTH;
      robot_positions[r].second = (MAP_HEIGHT + (py + vy) % MAP_HEIGHT) % MAP_HEIGHT;
      area_map[px][py] = '.';
      area_map[robot_positions[r].first][robot_positions[r].second] = '#';
    }
    int longest_line = 0;
    for (int r = 0; r < MAP_HEIGHT; r += 1) {
      int line = area_map[r][0] == '#' ? 1 : 0;
      for (int c = 1; c < MAP_WIDTH; c += 1) {
        if (area_map[r][c - 1] == '#') {
          line += 1;
        } else {
          if (line > longest_line) longest_line = line;
          line = 0;
        }
      }
    }
    if (longest_line > 10) {
      cout << i << endl;
      cout << longest_line << endl;
      print(area_map);
    }
  }
}
