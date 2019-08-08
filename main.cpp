#include "project2.h"
#include <iostream>
#include <vector>
#include <random>
#include <fstream>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<double> dist{0.0, 1.0};


std::vector<double> get_items(int n) {
  std::vector<double> items = std::vector<double>(n);
  for(int i = 0; i < n; i++) {
    items[i] = dist(gen);
  }
  return items;
}

double get_sum(const std::vector<double>& items) {
  double sum = 0.0;
  for(double item : items) {
    sum += item;
  }
  return sum;
}

void add_header(std::ofstream& f) {
  f << "funcname,n,waste" << std::endl;
}

void add_waste_to_file(std::ofstream& f, std::string funcname, int n, double waste) {
  f << funcname << "," << n << "," << waste << std::endl;
}

int main() {
  
  void (*funcs[5])(const std::vector<double>&, std::vector<int>&, std::vector<double>&) = 
  {next_fit, first_fit, first_fit_decreasing, best_fit, best_fit_decreasing};

  const char* names[] = {"next", "first", "first_decreasing", "best", "best_decreasing"};

  int N[] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768};

  std::ofstream f;
  f.open("waste.csv", std::ios::trunc);
  add_header(f);

  for(int n : N) {
    for(int fi = 0; fi < 5; fi++) {
      double total_waste = 0.0;
      const char *name = names[fi];
      for(int i = 0; i < 50; i++) {
      
        std::vector<double> items = get_items(n);
        std::vector<int> assignment(items.size(), 0);
        std::vector<double> free_space;

        funcs[fi](items, assignment, free_space);

        total_waste += ((double)free_space.size() - get_sum(items));
      
      }
      double waste = total_waste/50.0;
      std::cout << name << "," << n << ": " << waste << std::endl;
      add_waste_to_file(f, name, n, waste);
    }
  }

  f.close();
  
  return 0;
}
