#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void print(vector<int> stuff) {
  for (int t : stuff) {
    if (t >= 0)
      cout << t;
    else
      cout << '.';
    cout << " ";
  }
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

  // string fileString = "12345";
  string fileString = lines[0];
  vector<int> files;
  for (int i = 0; i < fileString.length(); i += 2) {
    int fileId = i / 2;
    int fileSize = fileString[i] - '0';
    for (int j = 0; j < fileSize; j += 1) {
      files.push_back(fileId);
    }
    if (i + 1 < fileString.length()) {
      int spaceSize = fileString[i + 1] - '0';
      for (int j = 0; j < spaceSize; j += 1) {
        files.push_back(-1);
      }
    }
  }

  int backInd = fileString.length() - 1;
  int backId = backInd / 2;
  int backSize = fileString[backInd] - '0';
  int backPosition = files.size();
  string modifiedFileString = fileString;

  while (backInd >= 0) {
    backId = backInd / 2;
    backSize = fileString[backInd] - '0';
    backPosition -= backSize;

    int filePosition = 0;
    for (int i = 1; i < backInd; i += 2) {
      filePosition += fileString[i - 1] - '0';
      int space = fileString[i] - '0';
      int actualSpace = modifiedFileString[i] - '0';
      if (actualSpace >= backSize) {
        int init = 0;
        // in case something already is in part of that space
        while (files[init + filePosition] != -1) {
          init += 1;
        }
        // update the filesystem
        for (int j = init; j < init + backSize; j += 1) {
          files[j + filePosition] = backId;
          files[j - init + backPosition] = -1;
        }
        // remove the amount of space filled in from the filestring
        modifiedFileString[i] = actualSpace - backSize + '0';
        break;
      }
      filePosition += space;
    }

    backPosition -= fileString[backInd - 1] - '0';
    backInd -= 2;
  }

  long long checkSum = 0;
  for (int i = 0; i < files.size(); i += 1) {
    if (files[i] != -1) {
      checkSum += i * files[i];
    }
  }

  cout << checkSum << endl;
}
