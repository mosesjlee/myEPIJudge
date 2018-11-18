#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int GetMaxTrappedWater(const vector<int>& heights) {
  // TODO - you fill in here.
  int max_water = 0;
  int i = 0; int j = heights.size()-1;
  while(i <= j) {
    int width = j-i;
    int height = heights[i] > heights[j] ? heights[j] : heights[i];
    
    int water = width * height;
    if(water > max_water) max_water = water;

    if(heights[i] > heights[j]) {
      j--;
    }
    else {
      i++;
    }
  }
  return max_water;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"heights"};
  return GenericTestMain(args, "max_trapped_water.cc", "max_trapped_water.tsv",
                         &GetMaxTrappedWater, DefaultComparator{}, param_names);
}
