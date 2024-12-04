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
  for (int i = 1; i < lines.size() - 1; i += 1) {
    for (int j = 1; j < lines[0].size() - 1; j += 1) {
      if (
        lines[i][j] == 'A'
        && ((lines[i-1][j-1] == 'S' && lines[i+1][j+1] == 'M') || (lines[i-1][j-1] == 'M' && lines[i+1][j+1] == 'S'))
        && ((lines[i+1][j-1] == 'S' && lines[i-1][j+1] == 'M') || (lines[i+1][j-1] == 'M' && lines[i-1][j+1] == 'S'))
      ) {
        nXmases += 1;
      }
    }
  }

  cout << nXmases << endl;
}
