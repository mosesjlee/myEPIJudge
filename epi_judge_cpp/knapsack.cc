#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Item {
  int weight, value;
};

int OptimumSubjectToCapacity(const vector<Item>& items, int capacity) {
  // TODO - you fill in here.
  vector<int> weight(capacity+1, 0);
  vector<vector<int>> knapsack(items.size(), weight);
  int max_val = 0;

  for(int i = items[0].weight; i < knapsack[0].size();i++) {
    knapsack[0][i] = items[0].value;
  }

  for(int i = 1; i < items.size(); i++) {
    for(int j = 1; j < knapsack.front().size(); j++) {
      if(items[i].weight > j) {
        max_val = knapsack[i-1][j];
      }
      else {
        max_val = std::max(knapsack[i-1][j], knapsack[i-1][j-items[i].weight]+items[i].value);
      }

      knapsack[i][j] = max_val;
    }
  }

  return max_val;
}
template <>
struct SerializationTraits<Item> : UserSerTraits<Item, int, int> {};

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"items", "capacity"};
  return GenericTestMain(args, "knapsack.cc", "knapsack.tsv",
                         &OptimumSubjectToCapacity, DefaultComparator{},
                         param_names);
}
