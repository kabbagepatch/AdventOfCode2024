#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
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

  map<string, vector<string>> all_connections;
  for (string line : lines) {
    string pc1 = line.substr(0, 2);
    string pc2 = line.substr(3, 2);

    all_connections[pc1].push_back(pc2);
    all_connections[pc2].push_back(pc1);
  }

  set<string> triple_connections;
  for (pair<string, vector<string>> connections_info : all_connections) {
    string pc1 = connections_info.first;
    vector<string> pc1_connections = connections_info.second;
    for (int i = 0; i < pc1_connections.size(); i += 1) {
      for (int j = 0; j < pc1_connections.size(); j += 1) {
        if (i == j) continue;

        string pc2 = pc1_connections[i];
        string pc3 = pc1_connections[j];
        vector<string> pc2_connections = all_connections[pc2];
        for (int k = 0; k < pc2_connections.size(); k += 1) {
          if (pc2_connections[k] == pc3) {
            string pcs[] = {pc1, pc2, pc3};
            sort(begin(pcs), end(pcs));
            string triple_connection = "";
            for (string pc : pcs) {
              triple_connection += pc;
            }
            triple_connections.insert(triple_connection);
          }
        }
      }
    }
  }

  cout << triple_connections.size() << endl;
  int chief_connections = 0;
  for (string triple_connection : triple_connections) {
    if (triple_connection[0] == 't' || triple_connection[2] == 't' || triple_connection[4] == 't') {
      chief_connections += 1;
    }
  }

  cout << chief_connections << endl;
}
