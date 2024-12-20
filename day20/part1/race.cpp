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

int main () {
  ifstream myfile;
  myfile.open ("../input");
  vector<string> maze;
  coords start;
  coords end;
  int i = 0;
  if (myfile.is_open()) {
    string line_string;
    while(getline(myfile, line_string)) {
      maze.push_back(line_string);
      for (int j = 0; j < line_string.length(); j += 1) {
        if (line_string[j] == 'S') {
          start.x = j;
          start.y = i;
        }
        if (line_string[j] == 'E') {
          end.x = j;
          end.y = i;
        }
      }
      i += 1;
    }
  }
  myfile.close();

  int default_time = get_shortest_path(maze, start, end).size() - 1;

  vector<coords> passable_walls;
  for (int i = 1; i < maze.size() - 1; i += 1) {
    for (int j = 1; j < maze[0].size() - 1; j += 1) {
      if (maze[i][j] == '#') {
        int empty_neighbors = 0;
        if (maze[i - 1][j] != '#') empty_neighbors += 1;
        if (maze[i + 1][j] != '#') empty_neighbors += 1;
        if (maze[i][j - 1] != '#') empty_neighbors += 1;
        if (maze[i][j + 1] != '#') empty_neighbors += 1;
        if (empty_neighbors > 1) {
          passable_walls.push_back({j, i});
        }
      }
    }
  }

  map<int, int> cheats;
  for (coords wall : passable_walls) {
    maze[wall.y][wall.x] = '.';
    int cheat_time = get_shortest_path(maze, start, end).size() - 1;
    int time_saved = default_time - cheat_time;
    if (time_saved >= 100) {
      if (cheats.find(time_saved) == cheats.end()) {
        cheats[time_saved] = 0;
      }
      cheats[time_saved] += 1;
    }
    maze[wall.y][wall.x] = '#';
  }

  int n_cheats = 0;
  for (pair<int, int> cheat : cheats) {
    n_cheats += cheat.second;
    cout << cheat.second << " cheats that save " << cheat.first << " picoseconds" << endl;
  }

  cout << n_cheats << endl;
}
