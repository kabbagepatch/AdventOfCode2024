#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <map>
using namespace std;

struct coords {
  int x;
  int y;
  bool operator==(const coords& other) const {
    return x == other.x && y == other.y;
  }
};

void print(string stuff) {
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

bool is_valid_to_move(coords c, const vector<string> &maze) {
  return c.x >= 0 && c.y >= 0 && c.y < maze.size() && c.x < maze[0].size() && maze[c.y][c.x] != '#';
}
vector<coords> get_shortest_path(vector<string> &maze, coords start, coords target, vector<vector<int>>& distances) {
  int rows = maze.size();
  int cols = maze[0].size();
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

int main () {
  ifstream myfile;
  myfile.open ("../input");
  vector<string> maze;
  coords start;
  coords end;
  int k = 0;
  if (myfile.is_open()) {
    string line_string;
    while(getline(myfile, line_string)) {
      maze.push_back(line_string);
      for (int l = 0; l < line_string.length(); l += 1) {
        if (line_string[l] == 'S') {
          start.x = l;
          start.y = k;
        }
        if (line_string[l] == 'E') {
          end.x = l;
          end.y = k;
        }
      }
      k += 1;
    }
  }
  myfile.close();

  int rows = maze.size();
  int cols = maze[0].size();
  vector<vector<int>> default_distances(rows, vector<int>(cols, INT16_MAX));
  int start_to_end = get_shortest_path(maze, start, end, default_distances).size();
  int default_time = start_to_end - 1;

  map<int, int> cheats;
  for (int i = 1; i < maze.size() - 1; i += 1) {
    for (int j = 1; j < maze[0].size() - 1; j += 1) {
      if (maze[i][j] == '.' || maze[i][j] == 'S') {
        for (int warp_distance = 2; warp_distance <= 20; warp_distance += 1) {
          vector<coords> warp_locations;
          for (int wx = -warp_distance; wx <= warp_distance; wx += 1) {
            int wy = warp_distance - abs(wx);
            if (is_valid_to_move({j + wx, i + wy}, maze)) warp_locations.push_back({j + wx, i + wy});
            if (wy != 0) {
              if (is_valid_to_move({j + wx, i - wy}, maze)) warp_locations.push_back({j + wx, i - wy});
            }
          }
          for (coords location : warp_locations) {
            int time_saved = default_distances[location.y][location.x] - (default_distances[i][j] + warp_distance);
            if (time_saved >= 100) {
              if (cheats.find(time_saved) == cheats.end()) {
                cheats[time_saved] = 0;
              }
              cheats[time_saved] += 1;
            }
          }
        }
      }
    }
  }

  int n_cheats = 0;
  for (pair<int, int> cheat : cheats) {
    n_cheats += cheat.second;
    cout << cheat.second << " cheats that save " << cheat.first << " picoseconds" << endl;
  }

  cout << n_cheats << endl;
}
