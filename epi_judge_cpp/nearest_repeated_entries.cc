#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include "test_framework/generic_test.h"
using std::string;
using std::vector;
#define BRUTE_FORCE
int FindNearestRepetition(const vector<string>& paragraph) {

  // TODO - you fill in here.
  int smallest_distance = INT_MAX;
#ifdef BRUTE_FORCE
#pragma message("BRUTE FORCE")
  std::unordered_map<string, std::pair<int, int>> word_list;

  for(int i = 0; i < paragraph.size(); i++) {
    auto it = word_list.find(paragraph[i]);
    if(it != word_list.end()) {
      int distance = i - it->second.first;
      it->second.second = fmin(it->second.second, distance);
      it->second.first = i;
    }
    else {
      word_list[paragraph[i]] = {i, INT_MAX};
    }
  }

  for(auto it : word_list) {
    smallest_distance = fmin(smallest_distance, it.second.second);
  }
#else
#pragma message("MY OPTIMIZED")
  std::unordered_map<string, std::pair<int, int>> word_list;

  for(int i = 0; i < paragraph.size(); i++) {
    auto it = word_list.find(paragraph[i]);
    if(it != word_list.end()) {
      it->second.second = fmin(it->second.second, (i - it->second.first));
      it->second.first = i;
      smallest_distance = fmin(smallest_distance, it->second.second);
    }
    else {
      word_list[paragraph[i]] = {i, INT_MAX};
    }
  }
#endif
  return smallest_distance != INT_MAX ? smallest_distance : -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"paragraph"};
  return GenericTestMain(args, "nearest_repeated_entries.cc",
                         "nearest_repeated_entries.tsv", &FindNearestRepetition,
                         DefaultComparator{}, param_names);
}
