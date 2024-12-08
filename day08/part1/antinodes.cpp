#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

void print(vector<string> stuff) {
  for (string t : stuff) {
    cout << t << endl;
  }
  cout << endl;
  cout << endl;
}

int manhattan_distance(pair<int, int> p1, pair<int, int> p2) {
  return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

bool are_collinear(pair<int, int> p1, pair<int, int> p2, pair<int, int> p3) {
    // Check area of the triangle formed by three points
    int area = (p2.first - p1.first) * (p3.second - p1.second) - (p2.second - p1.second) * (p3.first - p1.first);
    return area == 0;
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

  map<char, vector<pair<int, int>>> antennae;
  for (int i = 0; i < lines.size(); i += 1) {
    for (int j = 0; j < lines[0].size(); j += 1) {
      if (lines[i][j] != '.') {
        if (antennae.find(lines[i][j]) == antennae.end()) {
          antennae[lines[i][j]] = vector<pair<int, int>>();
        }
        antennae[lines[i][j]].push_back(make_pair(i, j));
      }
    }
  }

  int n_antinodes = 0;
  for (int i = 0; i < lines.size(); i += 1) {
    for (int j = 0; j < lines[0].size(); j += 1) {
      pair<int, int> cur_location = make_pair(i, j);
      bool antinode_found = false;

      // check each antenna frequency
      for (const pair<char, vector<pair<int, int>>> antenna : antennae ) {
        if (antinode_found) break;
        char label = antenna.first;
        vector<pair<int, int>> locations = antenna.second;
        vector<int> distances;
        // get all the distances
        for (pair<int, int> location : locations) {
          distances.push_back(manhattan_distance(location, cur_location));
        }

        // find antinodes by checking pairs of antennae
        for (size_t a1 = 0; a1 < locations.size(); a1 += 1) {
          for (size_t a2 = 0; a2 < locations.size(); a2 += 1) {
            if (a1 != a2 && are_collinear(locations[a1], locations[a2], cur_location)) {
              int d1 = manhattan_distance(locations[a1], cur_location);
              int d2 = manhattan_distance(locations[a2], cur_location);
              if (d1 == 2 * d2 || d1 == 2 * d2) {
                n_antinodes += 1;
                antinode_found = true;
                break;
              }
            }
            if (antinode_found) break;
          }
        }
      }
    }
  }

  cout << n_antinodes << endl;
}
