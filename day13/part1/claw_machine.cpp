#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

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

const string BUTTON_PREFIX = "Button Q: X+";
const string PRIZE_PREFIX = "Prize: X=";

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

  int n_tokens = 0;
  for (int i = 0; i < lines.size(); i += 4) {
    string button_a = lines[i];
    string button_b = lines[i + 1];
    string prize = lines[i + 2];

    int button_comma_ind = button_a.find(", ");
    float a_x = stoi(button_a.substr(BUTTON_PREFIX.size(), BUTTON_PREFIX.size() + button_comma_ind));
    float a_y = stoi(button_a.substr(button_comma_ind + 4));
    float b_x = stoi(button_b.substr(BUTTON_PREFIX.size(), BUTTON_PREFIX.size() + button_comma_ind));
    float b_y = stoi(button_b.substr(button_comma_ind + 4));

    int prize_comma_ind = prize.find(", ");
    float p_x = stoi(prize.substr(PRIZE_PREFIX.size(), PRIZE_PREFIX.size() + prize_comma_ind));
    float p_y = stoi(prize.substr(prize_comma_ind + 4));

    int det = a_x * b_y - a_y * b_x;
    if (det == 0) continue;

    float a_solution = abs((b_x * p_y - p_x * b_y) / det);
    float b_solution = abs((a_x * p_y - p_x * a_y) / det);
    if (int(a_solution) != a_solution || int(b_solution) != b_solution) continue;
    if (a_solution > 100 || b_solution > 100) continue;

    n_tokens += (3 * a_solution + b_solution);
  }

  cout << n_tokens << endl;
}
