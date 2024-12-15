#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

const int MAP_WIDTH = 101;
const int MAP_HEIGHT = 103;
const int TIME = 100;

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
  regex pattern("p=(\\d+),(\\d+) v=(-?\\d+),(-?\\d+)");
  for (string line : lines) {
    smatch matches;
    regex_search(line, matches, pattern);
    int px = stoi(matches[1]);
    int py = stoi(matches[2]);

    int vx = stoi(matches[3]);
    int vy = stoi(matches[4]);

    int final_px = (MAP_WIDTH + (px + (vx * TIME)) % MAP_WIDTH) % MAP_WIDTH;
    int final_py = (MAP_HEIGHT + (py + (vy * TIME)) % MAP_HEIGHT) % MAP_HEIGHT;
    robot_positions.push_back(make_pair(final_px, final_py));
  }

  int q1 = 0;
  int q2 = 0;
  int q3 = 0;
  int q4 = 0;
  for (pair<int, int> robot_position : robot_positions) {
    int px = robot_position.first;
    int py = robot_position.second;
    if (px < ((MAP_WIDTH - 1) / 2)) {
      if (py < ((MAP_HEIGHT - 1) / 2)) q1 += 1;
      if (py > ((MAP_HEIGHT - 1) / 2)) q3 += 1;
    }
    if (px > ((MAP_WIDTH - 1) / 2)) {
      if (py < ((MAP_HEIGHT - 1) / 2)) q2 += 1;
      if (py > ((MAP_HEIGHT - 1) / 2)) q4 += 1;
    }
  }

  int safety_factor = q1 * q2 * q3 * q4;

  cout << safety_factor << endl;
}
