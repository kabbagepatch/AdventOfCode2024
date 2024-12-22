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
  vector<vector<int>> all_prices;
  for (string line : lines) {
    vector<int> prices;
    long initial_secret = stol(line);
    long prev_secret = initial_secret;
    long cur_secret;
    prices.push_back(initial_secret % 10);
    for (int i = 0; i < 2000; i += 1) {
      cur_secret = prev_secret;
      cur_secret = (cur_secret * 64) ^ cur_secret;
      cur_secret %= 16777216;
      cur_secret = (cur_secret / 32) ^ cur_secret;
      cur_secret %= 16777216;
      cur_secret = (cur_secret * 2048) ^ cur_secret;
      cur_secret %= 16777216;
      prev_secret = cur_secret;
      prices.push_back(cur_secret % 10);
    }
    sum += cur_secret;
    all_prices.push_back(prices);
  }

  map<string, vector<int>> all_sequence_prices;
  for (int a = 0; a < all_prices.size(); a += 1) {
    vector<int> prices = all_prices[a];
    for (int p = 0; p < prices.size() - 4; p += 1) {
      int i = prices[p + 1] - prices[p];
      int j = prices[p + 2] - prices[p + 1];
      int k = prices[p + 3] - prices[p + 2];
      int l = prices[p + 4] - prices[p + 3];

      string sequence = to_string(i) + to_string(j) + to_string(k) + to_string(l);
      int existing_size = all_sequence_prices[sequence].size();
      for (; existing_size < a; existing_size += 1) {
        all_sequence_prices[sequence].push_back(0);
      }
      if (existing_size == a) {
        all_sequence_prices[sequence].push_back(prices[p + 4]);
      }
    }
  }

  int max_bananas = 0;
  string max_bananas_sequence;
  for (pair<string, vector<int>> sequence_prices : all_sequence_prices) {
    int n_bananas = 0;
    vector<int> prices = sequence_prices.second;
    for (int p : prices) {
      n_bananas += p;
    }
    if (n_bananas > max_bananas) {
      max_bananas = n_bananas;
      max_bananas_sequence = sequence_prices.first;
    }
  }

  cout << max_bananas << endl;
  cout << max_bananas_sequence << endl;
}
