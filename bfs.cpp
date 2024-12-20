#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

struct coords {
  int x;
  int y;
  bool operator==(const coords& other) const {
    return x == other.x && y == other.y;
  }
};

const vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool is_valid_to_move(coords c, const vector<string> &maze) {
  return c.x >= 0 && c.y >= 0 && c.y < maze.size() && c.x < maze[0].size() && maze[c.y][c.x] == '.';
}
vector<coords> get_shortest_path(vector<string> &maze, coords start, coords target) {
  int rows = maze.size();
  int cols = maze[0].size();
  vector<vector<int>> distances(rows, vector<int>(cols, INT16_MAX));
  vector<vector<coords>> parents(rows, vector<coords>(cols));

  queue<coords> q;
  q.push({start.x, start.y});
  distances[start.y][start.x] = 0;
  parents[start.y][start.x] = {-1, -1};

  while(!q.empty()) {
    coords current = q.front();
    q.pop();

    if (current.x == target.x && current.y == target.y) {
      break;
    }

    for (pair<int, int> d : directions) {
      coords neighbor = {current.x + d.first, current.y + d.second};

      if (is_valid_to_move(neighbor, maze) && distances[neighbor.y][neighbor.x] == INT16_MAX) {
        distances[neighbor.y][neighbor.x] = distances[current.y][current.x] + 1;
        parents[neighbor.y][neighbor.x] = current;
        q.push(neighbor);
      }
    }
  }
  
  vector<coords> shortest_path;

  if (distances[target.y][target.x] == INT16_MAX) {
    return shortest_path;
  }

  coords cur_parent = target;
  while (cur_parent.y != -1) {
    shortest_path.push_back(cur_parent);
    cur_parent = parents[cur_parent.y][cur_parent.x];
  }

  return shortest_path;
}
