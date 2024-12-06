#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

enum directions {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

void print(vector<string> stuff) {
  for (string t : stuff) {
    cout << t << endl;
  }
  cout << endl;
  cout << endl;
}

int main () {
  ifstream myfile;
  myfile.open ("../testinput");
  vector<string> areaMap;
  int i = 0;
  int guardX = -1;
  int guardY = -1;
  if (myfile.is_open()) {
    string lineString;
    while(getline(myfile, lineString)) {
      areaMap.push_back(lineString);
      if (guardX == -1) {
        for (int j = 0; j < lineString.size(); j += 1) {
          if (lineString[j] == '^') {
            guardX = i;
            guardY = j;
          }
        }
      }
      i += 1;
    }
  }
  myfile.close();

  int guardDirection = UP;
  bool guardOutOfBounds = false;
  areaMap[guardX][guardY] = 'X';
  while (!guardOutOfBounds) {
    switch (guardDirection) {
      case UP:
        if (guardX - 1 < 0) {
          guardOutOfBounds = true;
        } else {
          if (areaMap[guardX - 1][guardY] == '#') {
            guardDirection = RIGHT;
          } else {
            areaMap[guardX - 1][guardY] = 'X';
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

  int nVisited = 0;
  for (string row : areaMap) {
    for (char c : row) {
      if (c == 'X') nVisited += 1;
    }
  }

  print(areaMap);

  cout << nVisited << endl;
}
