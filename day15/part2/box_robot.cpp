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

bool can_move_box(vector<string>& area, coords cur_position, char direction, bool move) {
  int x1 = cur_position.x;
  int y = cur_position.y;
  int x2 = area[y][x1] == '[' ? x1 + 1 : x1 - 1;
  int next_y = direction == '^' ? y - 1 : y + 1;

  char at_next_x1 = area[next_y][x1];
  char at_next_x2 = area[next_y][x2];

  if (at_next_x1 == '#' || at_next_x2 == '#') return false;

  bool can_move = true;

  if (at_next_x1 == '.' && at_next_x2 == '.') {
    can_move = true;
  }

  if (at_next_x1 == area[y][x1]) {
    coords next_position;
    next_position.x = x1;
    next_position.y = next_y;
    can_move = can_move_box(area, next_position, direction, move);
  } else {
    if (at_next_x1 != '.') {
      coords next_position;
      next_position.x = x1;
      next_position.y = next_y;
      can_move = can_move && can_move_box(area, next_position, direction, move);
    }

    if (at_next_x2 != '.') {
      coords next_position;
      next_position.x = x2;
      next_position.y = next_y;
      can_move = can_move && can_move_box(area, next_position, direction, move);
    }
  }

  if (move) {
    area[next_y][x1] = area[y][x1];
    area[y][x1] = '.';
    area[next_y][x2] = area[y][x2];
    area[y][x2] = '.';
  }

  return can_move;
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
        string line_string2 = "";
        for (char c : line_string) {
          switch(c) {
            case '#': line_string2 += "##"; break;
            case '.': line_string2 += ".."; break;
            case 'O': line_string2 += "[]"; break;
            case '@': line_string2 += "@."; break;
          }
        }
        area.push_back(line_string2);
        size_t robot_x = line_string.find('@');
        if (robot_x != string::npos) {
          robot.x = robot_x * 2;
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
  cout << endl;
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
    } 
    
    if (area[next.y][next.x] == '[' || area[next.y][next.x] == ']') {
      if (c == '<' || c == '>') {
        coords next_non_box;
        next_non_box.x = next.x;
        next_non_box.y = next.y;
        while (area[next_non_box.y][next_non_box.x] == '[' || area[next_non_box.y][next_non_box.x] == ']') {
          next_non_box.x = c == '<' ? next_non_box.x - 2 : next_non_box.x + 2;
        }
        if (area[next_non_box.y][next_non_box.x] == '.') {
          if (c == '<') {
            for (int i = next.x; i >= next_non_box.x; i -= 1) {
              area[next.y][i] = area[next.y][i] == '[' ? ']' : '[';
            }
          } else {
            for (int i = next.x; i <= next_non_box.x; i += 1) {
              area[next.y][i] = area[next.y][i] == ']' ? '[' : ']';
            }
          }
          area[next.y][next.x] = '@';
          area[robot.y][robot.x] = '.';
          robot.x = next.x;
          robot.y = next.y;
        }
      } else {
        if (can_move_box(area, next, c, false)) {
          can_move_box(area, next, c, true);
          area[next.y][next.x] = '@';
          area[robot.y][robot.x] = '.';
          robot.x = next.x;
          robot.y = next.y;
        }
      }
    }
  }
  
  print(area);

  int sum = 0;
  for (int i = 0; i < area.size(); i += 1) {
    for (int j = 0; j < area[0].size(); j += 1) {
      if (area[i][j] == '[') {
        sum += 100 * i + j;
      }
    }
  }

  print(sum);
}
