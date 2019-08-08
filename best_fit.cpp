#include "project2.h"


void best_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
{
  int n = items.size();
  int b = 1;
  free_space.push_back(1.0);  

  for(int i = 0; i < n; i++) {
    double weight = items[i];
    double min = 1.1;
    int min_b = 0;

    for(int j = 0; j < b; j++) {
      if (weight <= free_space[j] && free_space[j] < min) {
        min = free_space[j];
        min_b = j;
      }
    }

    if(min == 1.1) {
      free_space.push_back(1.0-weight);
      assignment[i] = b;
      b++;
      continue;
    }

    free_space[min_b] -= weight;
    assignment[i] = min_b;
  }
}

void best_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
{
  std::vector<double> items_copy = items;
  std::sort(items_copy.begin(), items_copy.end(), std::greater<double>());
  best_fit(items_copy, assignment, free_space);
}
