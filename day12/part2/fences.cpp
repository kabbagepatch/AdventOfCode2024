#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

void print(vector<string> stuff) {
  for (string t : stuff) {
    cout << t << endl;
  }
  cout << endl;
  cout << endl;
}

void print(vector<vector<int>> stuff) {
  for (vector<int> t : stuff) {
    for (int i : t) {
      cout << (char)((i % 26) + 'a');
    }
    cout << endl;
  }
  cout << endl;
}


bool is_plot_adjacent_to_another(vector<string>& area, int i, int j) {
  char plot_type = area[i][j];
  return (
    (i > 0 && area[i - 1][j] == plot_type)
    || (i < area.size() - 1 && area[i + 1][j] == plot_type)
    || (j > 0 && area[i][j - 1] == plot_type)
    || (j < area[0].size() - 1 && area[i][j + 1] == plot_type)
  );
}

bool is_plot_adjacent_to_another(vector<vector<int>>& area, int i, int j, int plot_type) {
  return (
    (i > 0 && area[i - 1][j] == plot_type)
    || (i < area.size() - 1 && area[i + 1][j] == plot_type)
    || (j > 0 && area[i][j - 1] == plot_type)
    || (j < area[0].size() - 1 && area[i][j + 1] == plot_type)
  );
}

int main () {
  ifstream myfile;
  myfile.open ("../input");
  vector<string> plots;
  if (myfile.is_open()) {
    string line_string;
    while(getline(myfile, line_string)) {
      plots.push_back(line_string);
    }
  }
  myfile.close();

  // relabele plots with a unique label (for distinct regions of the same type)
  map<char, vector<int>> plot_mappings; // to map a type with a set of new labels
  int cur_plot = 0;
  vector<vector<int>> relabeled_plots(plots.size());
  for (int i = 0; i < plots.size(); i += 1) {
    relabeled_plots[i] = vector<int>(plots[0].size());
  }
  for (int i = 0; i < plots.size(); i += 1) {
    string row = plots[i];
    for (int j = 0; j < plots[0].size(); j += 1) {
      char plot = row[j];
      if (plot_mappings.find(plot) == plot_mappings.end()) { // existing mapping not found; new type discovered
        cur_plot += 1;
        plot_mappings[plot].push_back(cur_plot);
        relabeled_plots[i][j] = cur_plot;
      } else { // existing mapping found; check if plot is adjacent to an existing region of the same type
        int existing_region = -1;
        for (int plot_mapping : plot_mappings[plot]) {
          if (is_plot_adjacent_to_another(relabeled_plots, i, j, plot_mapping)) {
            if (existing_region == -1) { // first adjacent existing region found
              existing_region = plot_mapping;
            } else { // plot is adjacent to two regions of the same type but labeled different. It's the same region! Mark them all with one label
              plot_mappings[plot].erase(remove(plot_mappings[plot].begin(), plot_mappings[plot].end(), plot_mapping), plot_mappings[plot].end());
              for (int k = 0; k <= i; k += 1) {
                for (int l = 0; l <= plots[0].size(); l += 1) {
                  if (relabeled_plots[k][l] == plot_mapping) {
                    relabeled_plots[k][l] = existing_region;
                  }
                }
              }
            }
          }
        }
        if (existing_region == -1) { // plot is part of no existing region. New region
          cur_plot += 1;
          plot_mappings[plot].push_back(cur_plot);
          relabeled_plots[i][j] = cur_plot;
        } else { // plot is part of an existing region
          relabeled_plots[i][j] = existing_region;
        }
      }
    }
  }

  vector<int> region_areas(cur_plot + 1, 0);
  vector<int> region_corners(cur_plot + 1, 0);

  for (int i = 0; i < relabeled_plots.size(); i += 1) {
    for (int j = 0; j < relabeled_plots[i].size(); j += 1) {
      int plot_type = relabeled_plots[i][j];
      region_areas[plot_type] += 1;
      int n_adjacent = 0;
      bool top_adjacent = i > 0 && relabeled_plots[i - 1][j] == plot_type;
      bool bottom_adjacent = i < relabeled_plots.size() - 1 && relabeled_plots[i + 1][j] == plot_type;
      bool left_adjacent = j > 0 && relabeled_plots[i][j - 1] == plot_type;
      bool right_adjacent = j < relabeled_plots[0].size() - 1 && relabeled_plots[i][j + 1] == plot_type;
      bool topleft_adjacent = i > 0 && j > 0 && relabeled_plots[i - 1][j - 1] == plot_type;
      bool topright_adjacent = i > 0 && j < relabeled_plots[0].size() - 1 && relabeled_plots[i - 1][j + 1] == plot_type;
      bool bottomleft_adjacent = i < relabeled_plots.size() - 1 && j > 0 && relabeled_plots[i + 1][j - 1] == plot_type;
      bool bottomright_adjacent = i < relabeled_plots.size() - 1 && j < relabeled_plots[0].size() - 1 && relabeled_plots[i + 1][j + 1] == plot_type;
      if (top_adjacent) n_adjacent += 1;
      if (bottom_adjacent) n_adjacent += 1;
      if (left_adjacent) n_adjacent += 1;
      if (right_adjacent) n_adjacent += 1;

      switch(n_adjacent) {
        case 0: region_corners[plot_type] += 4; break;
        case 1: region_corners[plot_type] += 2; break;
        case 2:
          if (top_adjacent && left_adjacent) {
            region_corners[plot_type] += topleft_adjacent ? 1 : 2;
          }
          if (top_adjacent && right_adjacent) {
            region_corners[plot_type] += topright_adjacent ? 1 : 2;
          }
          if (bottom_adjacent && left_adjacent) {
            region_corners[plot_type] += bottomleft_adjacent ? 1 : 2;
          }
          if (bottom_adjacent && right_adjacent) {
            region_corners[plot_type] += bottomright_adjacent ? 1 : 2;
          }
          break;
        case 3:
          if (top_adjacent && left_adjacent && right_adjacent) {
            if (!topleft_adjacent) region_corners[plot_type] += 1;
            if (!topright_adjacent) region_corners[plot_type] += 1;
          }
          if (top_adjacent && left_adjacent && bottom_adjacent) {
            if (!topleft_adjacent) region_corners[plot_type] += 1;
            if (!bottomleft_adjacent) region_corners[plot_type] += 1;
          }
          if (top_adjacent && right_adjacent && bottom_adjacent) {
            if (!bottomright_adjacent) region_corners[plot_type] += 1;
            if (!topright_adjacent) region_corners[plot_type] += 1;
          }
          if (bottom_adjacent && left_adjacent && right_adjacent) {
            if (!bottomleft_adjacent) region_corners[plot_type] += 1;
            if (!bottomright_adjacent) region_corners[plot_type] += 1;
          }
          break;
        case 4:
          if (!topleft_adjacent) region_corners[plot_type] += 1;
          if (!topright_adjacent) region_corners[plot_type] += 1;
          if (!bottomleft_adjacent) region_corners[plot_type] += 1;
          if (!bottomright_adjacent) region_corners[plot_type] += 1;
          break;
        default: break;
      }
    }
  }

  int price = 0;
  for (int i = 1; i <= cur_plot; i += 1) {
    price += region_corners[i] * region_areas[i];
  }

  cout << price << endl;
}
