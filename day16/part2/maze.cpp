#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;

enum direction {
  N, S, W, E
};

struct coords {
  int x;
  int y;
  int score;
  direction d;
  bool operator<(const coords& other) const {
    return score > other.score;  // Min-heap based on score
  }
  bool operator==(const coords& other) const {
    return x == other.x && y == other.y;
  }
};

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
  cout << endl;
}

vector<coords> get_neighbors(vector<string>& maze, coords current) {
  vector<coords> neighbors;
  if (maze[current.y - 1][current.x] != '#' && current.d != S) neighbors.push_back({current.x, current.y - 1, 0, N});
  if (maze[current.y + 1][current.x] != '#' && current.d != N) neighbors.push_back({current.x, current.y + 1, 0, S});
  if (maze[current.y][current.x - 1] != '#' && current.d != E) neighbors.push_back({current.x - 1, current.y, 0, W});
  if (maze[current.y][current.x + 1] != '#' && current.d != W) neighbors.push_back({current.x + 1, current.y, 0, E});

  return neighbors;
}

int get_score(vector<string>& maze, coords current, coords next) {
  if (current.d == next.d) {
    return 1;
  }

  if (
    ((current.d == N || current.d == S) && (next.d == W || next.d == E))
    || ((current.d == W || current.d == E) && (next.d == N || next.d == S))
  ) {
    return 1001;
  }

  return 2001;
}

void mark_path_to_start(coords current, coords start, vector<vector<vector<coords>>>& all_parents, vector<vector<vector<bool>>>& visited, vector<string>& maze) {
  if (visited[current.y][current.x][current.d]) return;
  visited[current.y][current.x][current.d] = true;
  maze[current.y][current.x] = 'O';
  if (current == start) {
    return;
  }

  vector<coords> parents = all_parents[current.y][current.x];
  int length = 0;
  for (coords parent : parents) {
    if (parent.score + get_score(maze, parent, current) != current.score) continue;
    mark_path_to_start(parent, start, all_parents, visited, maze);
  }
}

int main () {
  ifstream myfile;
  myfile.open ("../input");
  vector<string> maze;
  if (myfile.is_open()) {
    string line_string;
    while(getline(myfile, line_string)) {
      maze.push_back(line_string);
    }
  }
  myfile.close();

  int n_rows = maze.size();
  int n_cols = maze[0].size();
  coords start = {1, n_rows - 2, 0, E};
  coords end = {n_cols - 2, 1, INT32_MAX};

  vector<vector<vector<int>>> score(n_rows, vector<vector<int>>(n_cols, vector<int>(4, INT32_MAX)));
  vector<vector<vector<coords>>> parents(n_rows, vector<vector<coords>>(n_cols, vector<coords>(4)));
  score[start.y][start.x][E] = 0;

  priority_queue<coords> pq;
  pq.push(start);

  while (!pq.empty()) {
    coords current = pq.top();
    pq.pop();
    if (current == end) {
      break;
    }

    vector<coords> neighbors = get_neighbors(maze, current);
    for (coords neighbor : neighbors) {
      int neighbor_score = current.score + get_score(maze, current, neighbor);
      if (score[neighbor.y][neighbor.x][current.d] >= neighbor_score) {
        score[neighbor.y][neighbor.x][current.d] = neighbor_score;
        parents[neighbor.y][neighbor.x][current.d] = current;
        neighbor.score = neighbor_score;
        pq.push(neighbor);
      }
    }
  }

  end.score = score[end.y][end.x][end.d];
  print(end.score);
  vector<vector<vector<bool>>> visited(n_rows, vector<vector<bool>>(n_cols, vector<bool>(4, false)));;
  mark_path_to_start(end, start, parents, visited, maze);
  int path = 0;
  for (int i = 0; i < maze.size(); i += 1) {
    for (int j = 0; j < maze[0].size(); j += 1) {
      if (maze[i][j] == 'O' || maze[i][j] == E) {
        path += 1;
      }
    }
  }
  print(path);
}
