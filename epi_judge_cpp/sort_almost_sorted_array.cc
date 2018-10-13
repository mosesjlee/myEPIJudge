#include <vector>
#include "test_framework/generic_test.h"
#include <queue>
using std::vector;
vector<int> SortApproximatelySortedData(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end, int k) {
  // TODO - you fill in here.
  vector<int> retval;

  std::priority_queue<int, vector<int>, std::greater<>> min_heap;
#ifdef BRUTE_FORCE
  while(sequence_begin != sequence_end) {
    min_heap.emplace(*sequence_begin);
    sequence_begin++;
  }
#else
#pragma message ("BOOK OPTIMIZED")
  for(int i = 0; i < k; i++) {
    min_heap.emplace(*sequence_begin++);
  }

  while(sequence_begin != sequence_end) {
    min_heap.push(*sequence_begin++);
    retval.emplace_back(min_heap.top());
    min_heap.pop();
  }

#endif
  while(!min_heap.empty()) {
    retval.emplace_back(min_heap.top());
    min_heap.pop();
  }

  return retval;
}
vector<int> SortApproximatelySortedDataWrapper(const vector<int>& sequence,
                                               int k) {
  return SortApproximatelySortedData(cbegin(sequence), cend(sequence), k);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence", "k"};
  return GenericTestMain(
      args, "sort_almost_sorted_array.cc", "sort_almost_sorted_array.tsv",
      &SortApproximatelySortedDataWrapper, DefaultComparator{}, param_names);
}
