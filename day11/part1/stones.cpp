#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

vector<long> split(string s, string delimiter) {
  vector<long> results;
  size_t pos = 0;
  string token;
  while ((pos = s.find(delimiter)) != string::npos) {
      token = s.substr(0, pos);
      results.push_back(stol(token));
      s.erase(0, pos + delimiter.length());
  }
  results.push_back(stol(s));
  return results;
}

void print(vector<long> stuff) {
  for (long t : stuff) {
    cout << t << " ";
  }
  cout << endl;
}

long get_n_digits(long number) {
  return log10(abs(number)) + 1;
}

bool has_even_digits(long number) {
  return get_n_digits(number) % 2 == 0;
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

  vector<long> stones = split(lines[0], " ");
  vector<long> new_stones;
  for (int i = 0; i < 25; i += 1) {
    new_stones.clear();
    for (long stone : stones) {
      if (stone == 0) {
        new_stones.push_back(1);
      } else if (has_even_digits(stone)) {
        long n_digits = get_n_digits(stone);
        long divisor = pow(10, n_digits / 2);
        new_stones.push_back(stone / divisor);
        new_stones.push_back(stone % divisor);
      } else {
        new_stones.push_back(stone * 2024);
      }
    }
    stones = new_stones;
  }

  cout << stones.size() << endl;
}
