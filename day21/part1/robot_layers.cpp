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
  coords cur_position = dirpad_positions.at('A');
  string sequence = "";
  for (char n : directional_code) {
    coords next_position = dirpad_positions.at(n);
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

  int complexity = 0;
  for (string code : codes) {
    string numpad_sequence = get_numpad_sequence(code, numpad_positions);
    string dirpad_sequence = get_dirpad_sequence(numpad_sequence, dirpad_positions);
    dirpad_sequence = get_dirpad_sequence(dirpad_sequence, dirpad_positions);

    long sequence_length = dirpad_sequence.length();
    int numeric_code = stoi(code.substr(0, code.size() - 1));
    complexity += sequence_length * numeric_code;
  }

  cout << complexity << endl;
}
