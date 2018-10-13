#include <vector>
#include <queue>
#include "test_framework/generic_test.h"
using std::vector;
//#define BRUTE_FORCE

vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
  // TODO - you fill in here.
#ifdef BRUTE_FORCE
#pragma message ("BRUTE FORCE")
  std::priority_queue<int, vector<int>, std::function<bool(int, int)>>
    min_heap([](const int & a, const int & b) {
      return a > b;
    });

  for(auto v : sorted_arrays) {
    for(int i : v) {
      min_heap.emplace(i);
    }
  }

  vector<int> retval;
  while(!min_heap.empty()) {
    retval.emplace_back(min_heap.top());
    min_heap.pop();
  }
  return retval;

#else

#pragma message ("attempting to optimize")
  std::priority_queue<int, vector<int>, std::greater<>> min_heap;
  vector<int> retval;
  int max_size = sorted_arrays[0].size();

  //Take advantage of already sorted arrays
  //Idea is that insert elements from each array
  //and take the pop from top becasue that is the 
  //smallest of the three
  //Need to rethink this through
  for(int i = 0; i < max_size; i++) {
    for(vector<int> v : sorted_arrays) {
      max_size = fmax(max_size, v.size());
      if(i >= v.size()) continue;
      min_heap.emplace(v[i]);
    }
    retval.emplace_back(min_heap.top());
    min_heap.pop();
  }

  while(!min_heap.empty()) {
    retval.emplace_back(min_heap.top());
    min_heap.pop();
  }
  return retval;
#endif
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}
