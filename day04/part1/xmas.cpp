#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void print(vector<string> stuff) {
  for (string t : stuff) {
    cout << t << endl;
  }
  cout << endl;
  cout << endl;
}

int main () {
  ifstream myfile;
  myfile.open ("../input");
  vector<string> lines;
  if (myfile.is_open()) {
    string lineString;
    while(getline(myfile, lineString)) {
      lines.push_back(lineString);
    }
  }
  myfile.close();

  int nXmases = 0;
  for (int i = 0; i < lines.size(); i += 1) {
    for (int j = 0; j < lines[0].size(); j += 1) {
      char curChar = lines[i][j];
      if (curChar == 'X') {
        // up
        if (i >= 3 && lines[i-1][j] == 'M' && lines[i-2][j] == 'A' && lines[i-3][j] == 'S') {
          nXmases += 1;
        }
        // down
        if (i < lines.size() - 3 && lines[i+1][j] == 'M' && lines[i+2][j] == 'A' && lines[i+3][j] == 'S') {
          nXmases += 1;
        }
        // left
        if (j >= 3 && lines[i][j-1] == 'M' && lines[i][j-2] == 'A' && lines[i][j-3] == 'S') {
          nXmases += 1;
        }
        // right
        if (j < lines[0].size() - 3 && lines[i][j+1] == 'M' && lines[i][j+2] == 'A' && lines[i][j+3] == 'S') {
          nXmases += 1;
        }
        // diagonal top-left
        if (i >= 3 && j >= 3 && lines[i-1][j-1] == 'M' && lines[i-2][j-2] == 'A' && lines[i-3][j-3] == 'S') {
          nXmases += 1;
        }
        // diagonal top-right
        if (i >= 3 && j < lines[0].size() - 3 && lines[i-1][j+1] == 'M' && lines[i-2][j+2] == 'A' && lines[i-3][j+3] == 'S') {
          nXmases += 1;
        }
        // diagonal bottom-left
        if (i < lines.size() - 3 && j >= 3 && lines[i+1][j-1] == 'M' && lines[i+2][j-2] == 'A' && lines[i+3][j-3] == 'S') {
          nXmases += 1;
        }
        // diagonal bottom-right
        if (i < lines.size() - 3 && j < lines[0].size() - 3 && lines[i+1][j+1] == 'M' && lines[i+2][j+2] == 'A' && lines[i+3][j+3] == 'S') {
          nXmases += 1;
        }
      }
    }
  }

  cout << nXmases << endl;
}
