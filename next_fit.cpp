#include "project2.h"


void next_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
{
  int n = items.size();
  int b = 1;
  free_space.push_back(1.0);
  
  for(int i = 0; i < n; i++) {
    double free = free_space[b-1];
    double weight = items[i];
    if (weight <= free) {
      free_space[b-1] -= weight;
      assignment[i] = b-1;
      continue;
    }
    free_space.push_back(1.0-weight);
    assignment[i] = b;
    b++;
  }
}

