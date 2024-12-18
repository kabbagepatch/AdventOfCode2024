#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <queue>
using namespace std;

struct coords {
  int x;
  int y;
  bool operator==(const coords& other) const {
    return x == other.x && y == other.y;
  }
};

void print(auto stuff) {
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
  cout << endl;
}


const vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool is_valid_to_move(coords current, const vector<string> &maze) {
  return current.x >= 0 && current.y >= 0 && current.y < maze.size() && current.x < maze[0].size() && maze[current.y][current.x] == '.';
}

int shortest_path(vector<string> &maze, coords start, coords target) {
  int rows = maze.size();
  int cols = maze[0].size();
  vector<vector<int>> distances(rows, vector<int>(cols, INT16_MAX));

  queue<coords> q;
  q.push({start.x, start.y});
  distances[start.y][start.x] = 0;

  while(!q.empty()) {
    coords current = q.front();
    q.pop();

    if (current.x == target.x && current.y == target.y) {
      return distances[current.y][current.x];
    }

    for (pair<int, int> d : directions) {
      coords neighbor = {current.x + d.first, current.y + d.second};

      if (is_valid_to_move(neighbor, maze) && distances[neighbor.y][neighbor.x] == INT16_MAX) {
        distances[neighbor.y][neighbor.x] = distances[current.y][current.x] + 1;
        q.push(neighbor);
      }
    }
  }

  return -1;
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

  print(lines);

  int MAP_WIDTH = 71;
  int MAP_HEIGHT = 71;
  int BYTES_FALLEN = 1024;

  vector<string> memory_space(MAP_HEIGHT, string(MAP_WIDTH, '.'));

  vector<pair<int, int>> bytes_falling;
  regex pattern("(\\d+),(\\d+)");
  for (string line : lines) {
    smatch matches;
    regex_search(line, matches, pattern);
    int x = stoi(matches[1]);
    int y = stoi(matches[2]);
    bytes_falling.push_back({x, y});
  }

  for (int i = 0; i < BYTES_FALLEN; i += 1) {
    memory_space[bytes_falling[i].second][bytes_falling[i].first] = '#';
  }

  print(memory_space);

  print(shortest_path(memory_space, {0, 0}, {MAP_WIDTH - 1, MAP_HEIGHT - 1}));
}
