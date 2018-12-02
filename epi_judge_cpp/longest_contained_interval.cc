#include <vector>
#include <unordered_set>
#include "test_framework/generic_test.h"
using std::vector;

int LongestContainedRange(const vector<int>& A) {
  // TODO - you fill in here.
  std::unordered_set<int> elements(A.begin(), A.end());
  int retval = 0;
  int curr_max = 0;
  int i = 0;

  while(!elements.empty() && i < A.size()) {
    int j = 1;
    curr_max = 1;
    while(elements.count(A[i]+j)) {
      elements.erase(A[i]+j);
      curr_max++;
      j++;
    }

    j = 1;
    while(elements.count(A[i]-j)) {
      elements.erase(A[i]-j);
      curr_max++;
      j++;
    }

    retval = std::max(retval, curr_max);
    elements.erase(A[i]);
    i++;
  }

  return retval;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(
      args, "longest_contained_interval.cc", "longest_contained_interval.tsv",
      &LongestContainedRange, DefaultComparator{}, param_names);
}
