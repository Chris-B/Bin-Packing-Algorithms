#include "project2.h"


void first_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
{
  int n = items.size();
  int b = 1;
  free_space.push_back(1.0);
  
  for(int i = 0; i < n; i++) {
    double weight = items[i];
    int j;
    for(j = 0; j < b; j++) {
      if (weight <= free_space[j]) {
        free_space[j] -= weight;
        assignment[i] = j;
        break;
      }
    }
    
    if(j == b) {
      free_space.push_back(1.0-weight);
      assignment[i] = b;
      b++;
    }
    
  }
}

void first_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)
{
  std::vector<double> items_copy = items;
  std::sort(items_copy.begin(), items_copy.end(), std::greater<double>());
  first_fit(items_copy, assignment, free_space);
}
