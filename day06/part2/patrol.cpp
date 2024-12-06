#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

enum directions {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

enum endConditions {
  OUT_OF_BOUNDS,
  IN_A_LOOP
};

void print(vector<string> stuff) {
  for (string t : stuff) {
    cout << t << endl;
  }
  cout << endl;
  cout << endl;
}

string getKey(int x, int y, directions d) {
  return to_string(x) + " " + to_string(y) + " " + to_string(d);
}

endConditions evaluateGuardPath(vector<string> &areaMap, int guardX, int guardY) {
  map<string, bool> visited;

  directions guardDirection = UP;
  bool guardOutOfBounds = false;
  bool guardInALoop = false;
  areaMap[guardX][guardY] = 'X';
  while (!guardOutOfBounds && !guardInALoop) {
    string key = getKey(guardX, guardY, guardDirection);
    if (visited.find(key) != visited.end()) {
      guardInALoop = true;
      break;
    }

    visited[key] = true;
    switch (guardDirection) {
      case UP:
        if (guardX - 1 < 0) {
          guardOutOfBounds = true;
        } else {
          if (areaMap[guardX - 1][guardY] == '#') {
            guardDirection = RIGHT;
          } else {
            guardX -= 1;
          }
        }
        break;
      
      case DOWN:
        if (guardX + 1 >= areaMap.size()) {
          guardOutOfBounds = true;
        } else {
          if (areaMap[guardX + 1][guardY] == '#') {
            guardDirection = LEFT;
          } else {
            areaMap[guardX + 1][guardY] = 'X';
            guardX += 1;
          }
        }
        break;

      case LEFT:
        if (guardY - 1 < 0) {
          guardOutOfBounds = true;
        } else {
          if (areaMap[guardX][guardY - 1] == '#') {
            guardDirection = UP;
          } else {
            areaMap[guardX][guardY - 1] = 'X';
            guardY -= 1;
          }
        }
        break;
      
      case RIGHT:
        if (guardY + 1 >= areaMap.size()) {
          guardOutOfBounds = true;
        } else {
          if (areaMap[guardX][guardY + 1] == '#') {
            guardDirection = DOWN;
          } else {
            areaMap[guardX][guardY + 1] = 'X';
            guardY += 1;
          }
        }
        break;
    }
  }

  if (guardInALoop) {
    return IN_A_LOOP;
  }

  return OUT_OF_BOUNDS;
}

int main () {
  ifstream myfile;
  myfile.open ("../input_modified");
  vector<string> areaMap;
  int r = 0;
  int guardX = -1;
  int guardY = -1;
  if (myfile.is_open()) {
    string lineString;
    while(getline(myfile, lineString)) {
      areaMap.push_back(lineString);
      if (guardX == -1) {
        for (int c = 0; c < lineString.size(); c += 1) {
          if (lineString[c] == '^') {
            guardX = r;
            guardY = c;
          }
        }
      }
      r += 1;
    }
  }
  myfile.close();

  int nLoops = 0;
  for (int i = 0; i < areaMap.size(); i += 1) {
    for (int j = 0; j < areaMap[0].size(); j += 1) {
      if (areaMap[i][j] == 'X') {
        areaMap[i][j] = '#';
        nLoops += evaluateGuardPath(areaMap, guardX, guardY);
        areaMap[i][j] = 'X';
      }
    }
  }

  cout << endl << nLoops << endl;
}
