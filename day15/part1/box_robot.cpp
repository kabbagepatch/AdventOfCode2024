#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct coords {
  int x;
  int y;
};

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

bool isNumber(char c) {
  return c >= '0' && c <= '9';
}

void print(string stuff) {
  cout << stuff << endl;
}

void print(int stuff) {
  cout << stuff << endl;
}

void print(coords stuff) {
  cout << stuff.x << ", " << stuff.y << endl;
}

void print(vector<string> stuff) {
  for (string t : stuff) {
    cout << t << endl;
  }
  cout << endl;
}

int main () {
  ifstream myfile;
  myfile.open ("../input");
  vector<string> area;
  string robot_instructions = "";
  bool reading_area = true;
  coords robot;
  if (myfile.is_open()) {
    string line_string;
    int cur_y = 0;
    while(getline(myfile, line_string)) {
      if (line_string.empty()) {
        reading_area = false;
        continue;
      }
      if (reading_area) {
        area.push_back(line_string);
        size_t robot_x = line_string.find('@');
        if (robot_x != string::npos) {
          robot.x = robot_x;
          robot.y = cur_y;
        }
        cur_y += 1;
      } else {
        robot_instructions += line_string;
      }
    }
  }
  myfile.close();

  print(area);
  // print(robot_instructions);
  print(robot);
  cout << endl;

  for (char c : robot_instructions) {
    coords next;
    next.x = robot.x;
    next.y = robot.y;
    switch(c) {
      case '^': next.y = robot.y - 1; break;
      case 'v': next.y = robot.y + 1; break;
      case '<': next.x = robot.x - 1; break;
      case '>': next.x = robot.x + 1; break;
    }
    if (area[next.y][next.x] == '.') {
      area[robot.y][robot.x] = '.';
      area[next.y][next.x] = '@';
      robot.x = next.x;
      robot.y = next.y;
    } else if (area[next.y][next.x] == 'O') {
      coords next_non_box;
      next_non_box.x = next.x;
      next_non_box.y = next.y;
      while (area[next_non_box.y][next_non_box.x] == 'O') {
        switch(c) {
          case '^': next_non_box.y = next_non_box.y - 1; break;
          case 'v': next_non_box.y = next_non_box.y + 1; break;
          case '<': next_non_box.x = next_non_box.x - 1; break;
          case '>': next_non_box.x = next_non_box.x + 1; break;
        }
      }
      if (area[next_non_box.y][next_non_box.x] == '.') {
        area[robot.y][robot.x] = '.';
        area[next.y][next.x] = '@';
        area[next_non_box.y][next_non_box.x] = 'O';
        robot.x = next.x;
        robot.y = next.y;
      }
    }
  }

  print(area);

  int sum = 0;
  for (int i = 0; i < area.size(); i += 1) {
    for (int j = 0; j < area[0].size(); j += 1) {
      if (area[i][j] == 'O') {
        sum += 100 * i + j;
      }
    }
  }

  print(sum);
}
