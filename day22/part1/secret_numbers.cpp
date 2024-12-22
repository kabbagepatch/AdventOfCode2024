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
    string line_string;
    while(getline(myfile, line_string)) {
      lines.push_back(line_string);
    }
  }
  myfile.close();

  long sum = 0;
  for (string line : lines) {
    long initial_secret = stol(line);
    long prev_secret = initial_secret;
    long cur_secret;
    for (int i = 0; i < 2000; i += 1) {
      cur_secret = prev_secret;
      cur_secret = (cur_secret * 64) ^ cur_secret;
      cur_secret %= 16777216;
      cur_secret = (cur_secret / 32) ^ cur_secret;
      cur_secret %= 16777216;
      cur_secret = (cur_secret * 2048) ^ cur_secret;
      cur_secret %= 16777216;
      prev_secret = cur_secret;
    }
    sum += cur_secret;
  }

  cout << sum << endl;
}
