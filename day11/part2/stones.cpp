#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
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
  map<long, long> stone_counts;
  for (long stone : stones) {
    if (stone_counts.find(stone) == stone_counts.end()) {
      stone_counts[stone] = 0;
    }
    stone_counts[stone] += 1;
  }

  for (int i = 0; i < 75; i += 1) {
    map<long, long> new_stone_counts;
    for (pair<long, long> stone_count : stone_counts) {
      long stone = stone_count.first;
      long count = stone_count.second;
      if (count == 0) {
        continue;
      }
      vector<long> new_stones;
      if (stone == 0) {
        new_stone_counts[1] += count;
      } else if (has_even_digits(stone)) {
        long n_digits = get_n_digits(stone);
        long divisor = pow(10, n_digits / 2);
        new_stone_counts[stone / divisor] += count;
        new_stone_counts[stone % divisor] += count;
      } else {
        new_stone_counts[stone * 2024] += count;
      }
    }
    stone_counts = new_stone_counts;
  }

  long long n_stones;
  for (pair<long, long> stone_count : stone_counts) {
    n_stones += stone_count.second;
  }

  cout << n_stones << endl;
}
