#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

struct coords {
  int x;
  int y;
  int score;
  char d;
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
  if (maze[current.y - 1][current.x] != '#') neighbors.push_back({current.x, current.y - 1, 0, 'N'});
  if (maze[current.y + 1][current.x] != '#') neighbors.push_back({current.x, current.y + 1, 0, 'S'});
  if (maze[current.y][current.x - 1] != '#') neighbors.push_back({current.x - 1, current.y, 0, 'W'});
  if (maze[current.y][current.x + 1] != '#') neighbors.push_back({current.x + 1, current.y, 0, 'E'});

  return neighbors;
}

int get_score(vector<string>& maze, coords current, coords next) {
  if (current.d == next.d) {
    return 1;
  }

  if (
    ((current.d == 'N' || current.d == 'S') && (next.d == 'W' || next.d == 'E'))
    || ((current.d == 'W' || current.d == 'E') && (next.d == 'N' || next.d == 'S'))
  ) {
    return 1001;
  }

  return 2001;
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
  coords start = {1, n_rows - 2, 0, 'E'};
  coords end = {n_cols - 2, 1, INT32_MAX};

  vector<vector<int>> score(n_rows, vector<int>(n_cols, INT32_MAX));
  score[start.y][start.x] = 0;

  priority_queue<coords> pq;
  pq.push(start);

  print(maze);

  while (!pq.empty()) {
    coords current = pq.top();
    pq.pop();
    if (current == end) {
      break;
    }

    vector<coords> neighbors = get_neighbors(maze, current);
    for (coords neighbor : neighbors) {
      int neighbor_score = current.score + get_score(maze, current, neighbor);
      if (score[neighbor.y][neighbor.x] > neighbor_score) {
        score[neighbor.y][neighbor.x] = neighbor_score;
        neighbor.score = neighbor_score;
        pq.push(neighbor);
      }
    }
  }

  print(score[end.y][end.x]);
}
