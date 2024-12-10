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

  string fileString = lines[0];
  long checkSum = 0;
  int frontInd = 0;
  int frontId = frontInd / 2;
  int frontSize = fileString[frontInd] - '0';
  int backInd = fileString.length() - 1;
  int backId = backInd / 2;
  int backSize = fileString[backInd] - '0';
  int position = 0;

  while (frontInd < backInd) {
    // Add the files from the front to the checksum
    for (int i = 0; i < frontSize; i += 1) {
      checkSum += position * frontId;
      position += 1;
    }
    frontInd += 2;
    frontId = frontInd / 2;
    frontSize = fileString[frontInd] - '0';

    // Add the files from the back to the checksum after moving them to the empty spaces
    int spaceSize = fileString[frontInd - 1] - '0';
    for (int i = 0; i < spaceSize; i += 1) {
      checkSum += position * backId;
      position += 1;
      backSize -= 1;
      if (backSize == 0) {
        backInd -= 2;
        backId = backInd / 2;
        backSize = fileString[backInd] - '0';
        if (frontInd >= backInd) {
          backSize = 0;
          break;
        }
      }
    }
  }

  if (backSize > 0) {
    checkSum += position * backId;
    position += 1;
  }

  cout << checkSum << endl;
}
