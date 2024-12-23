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

map<string, vector<string>> longest_connection_cache;

vector<string> get_longest_connection_for_pc(string pc, vector<string> existing_connections, map<string, map<string, bool>>& all_connections) {
  sort(existing_connections.begin(), existing_connections.end());
  string key = pc + "-";
  for (string ec : existing_connections) {
    key += ec;
  }
  if (longest_connection_cache.find(key) != longest_connection_cache.end()) {
    return longest_connection_cache[key];
  }

  map<string, bool> pc_connections = all_connections[pc];
  for (string ec : existing_connections) {
    if (!pc_connections[ec]) {
      longest_connection_cache[key] = existing_connections;
      return existing_connections;
    }
  }

  existing_connections.push_back(pc);
  vector<string> longest_connection = existing_connections;
  for (pair<string, bool> connection : pc_connections) {
    string pc2 = connection.first;
    bool connection_exists = false;
    for (string ec : existing_connections) {
      if (pc2 == ec) {
        connection_exists = true;
        break;
      }
    }
    if (connection_exists) continue;

    vector<string> longest_connection_for_pc = get_longest_connection_for_pc(pc2, existing_connections, all_connections);
    if (longest_connection_for_pc.size() > longest_connection.size()) {
      longest_connection = longest_connection_for_pc;
    }
  }

  longest_connection_cache[key] = longest_connection;
  return longest_connection;
}

vector<string> get_longest_connection(map<string, map<string, bool>>& all_connections) {
  vector<string> longest_connection;
  for (pair<string, map<string, bool>> connections : all_connections) {
    string pc = connections.first;
    vector<string> longest_connection_for_pc = get_longest_connection_for_pc(pc, {}, all_connections);
    if (longest_connection_for_pc.size() > longest_connection.size()) {
      longest_connection = longest_connection_for_pc;
    }
  }

  return longest_connection;
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

  map<string, map<string, bool>> all_connections;
  for (string line : lines) {
    string pc1 = line.substr(0, 2);
    string pc2 = line.substr(3, 2);

    all_connections[pc1][pc2] = true;
    all_connections[pc2][pc1] = true;
  }

  vector<string> longest_connection = get_longest_connection(all_connections);
  string password = "";
  for (string connection : longest_connection) {
    password += connection + ",";
  }
  password = password.substr(0, password.length() - 1);

  cout << password << endl;
}
