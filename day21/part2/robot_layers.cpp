#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct coords {
  int r;
  int c;
  bool operator==(const coords& other) const {
    return r == other.r && c == other.c;
  }
  bool operator!=(const coords& other) const {
    return r != other.r || c != other.c;
  }
};

vector<string> split(string s, string delimiter) {
  vector<string> results;
  size_t pos = 0;
  string token;
  while ((pos = s.find(delimiter)) != string::npos) {
      token = s.substr(0, pos);
      results.push_back(token);
      s.erase(0, pos + delimiter.length());
  }
  results.push_back(s);
  return results;
}

bool isNumber(char c) {
  return c >= '0' && c <= '9';
}

void print(string stuff) {
  cout << stuff << endl;
}

void print(coords stuff) {
  cout << stuff.c << ", " << stuff.r << endl;
}

void print(vector<string> stuff) {
  for (string t : stuff) {
    cout << t << endl;
  }
  cout << endl;
  cout << endl;
}

const vector<string> numeric_pad = {"789", "456", "123", " 0A"};
const vector<string> directional_pad = {" ^A", "<v>"};

string get_sequence_from(const coords& cur_position, const coords& next_position) {
  vector<string> sequences;
  string sequence = "";
  bool moving_horizontally = cur_position.c != next_position.c;
  bool moving_vertically = cur_position.r != next_position.r;
  
  for (int c = cur_position.c; c > next_position.c; c -= 1) {
    sequence += '<';
  }
  for (int r = cur_position.r; r < next_position.r; r += 1) {
      sequence += 'v';
  }
  for (int r = cur_position.r; r > next_position.r; r -= 1) {
    sequence += '^';
  }
  for (int c = cur_position.c; c < next_position.c; c += 1) {
    sequence += '>';
  }

  sequence += 'A';

  return sequence;
}

string get_numpad_sequence(string numeric_code, const map<char, coords>& numpad_positions) {
  coords cur_position = numpad_positions.at('A');
  vector<string> sequences;
  string sequence = "";
  for (char n : numeric_code) {
    coords next_position = numpad_positions.at(n);
    if (cur_position.r == 3 && next_position.c == 0) {
      for (int r = cur_position.r; r > next_position.r; r -= 1) {
        cur_position.r -= 1;
        sequence += '^';
      }
    }
    if (cur_position.c == 0 && next_position.r == 3) {
      for (int c = cur_position.c; c < next_position.c; c += 1) {
        sequence += '>';
        cur_position.c += 1;
      }
    }
    sequence += get_sequence_from(cur_position, next_position);
    cur_position = next_position;
  }

  return sequence;
}

string get_dirpad_sequence(string directional_code, const map<char, coords>& dirpad_positions) {
  coords cur_position = dirpad_positions.at(directional_code[0]);
  string sequence = "";
  for (int i = 1; i < directional_code.length(); i += 1) {
    char n = directional_code[i];
    coords next_position = dirpad_positions.at(n);
    if (cur_position.r == 0 && n == '<') {
      sequence += 'v';
      cur_position.r += 1;
    }
    if (cur_position.c == 0) {
      for (int c = cur_position.c; c < next_position.c; c += 1) {
        sequence += '>';
        cur_position.c += 1;
      }
    }

    sequence += get_sequence_from(cur_position, next_position);
    cur_position = next_position;
  }

  return sequence;
}

int main () {
  ifstream myfile;
  myfile.open ("../input");
  vector<string> codes;
  if (myfile.is_open()) {
    string line_string;
    while(getline(myfile, line_string)) {
      codes.push_back(line_string);
    }
  }
  myfile.close();

  map<char, coords> numpad_positions;
  for (int i = 0; i < numeric_pad.size(); i += 1) {
    for (int j = 0; j < numeric_pad[0].size(); j += 1) {
      numpad_positions[numeric_pad[i][j]] = {i, j};
    }
  }

  map<char, coords> dirpad_positions;
  for (int i = 0; i < directional_pad.size(); i += 1) {
    for (int j = 0; j < directional_pad[0].size(); j += 1) {
      dirpad_positions[directional_pad[i][j]] = {i, j};
    }
  }

  map<string, string> move_sequences;
  string dpad_keys = "<>v^A";
  for (int i = 0; i < dpad_keys.size(); i += 1) {
    for (int j = 0; j < dpad_keys.size(); j += 1) {
      string pair = "";
      pair.push_back(dpad_keys[i]);
      pair.push_back(dpad_keys[j]);
      move_sequences[pair] = get_dirpad_sequence(pair, dirpad_positions);
    }
  }

  long long complexity = 0;
  for (string code : codes) {
    string sequence = get_numpad_sequence(code, numpad_positions);
    map<string, long long> move_counts;
    map<string, long long> sequence_counts;
    sequence_counts[sequence] = 1;
    for (int d = 0; d < 26; d += 1) {
      move_counts.clear();
      for (pair<string, long long> sequence_count : sequence_counts) {
        string next_sequence = "A" + sequence_count.first;
        for (int i = 0; i < next_sequence.size() - 1; i += 1) {
          string move = next_sequence.substr(i, 2);
          if (move_counts.find(move) == move_counts.end()) {
            move_counts[move] = 0;
          }
          move_counts[move] += sequence_count.second;
        }
      }
      sequence_counts.clear();
      for (pair<string, long long> move_count : move_counts) {
        string move = move_count.first;
        long count = move_count.second;
        string sequence = move_sequences[move];
        if (sequence_counts.find(sequence) == sequence_counts.end()) {
          sequence_counts[sequence] = 0;
        }
        sequence_counts[sequence] += move_count.second;
      }
    }

    long long sequence_length = 0;
    for (pair<string, long long> move_count : move_counts) {
      sequence_length += move_count.second;
    }
    int numeric_code = stoi(code.substr(0, code.size() - 1));
    complexity += sequence_length * numeric_code;
  }

  cout << complexity << endl;
}
