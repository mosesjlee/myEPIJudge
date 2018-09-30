#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
bool CanReachEnd(const vector<int>& max_advance_steps) {
  // TODO - you fill in here.
  if(max_advance_steps.size() == 1) return true;

  int furthest = 0;
  for(int i = 0; i < max_advance_steps.size(); i++) {
    furthest = fmax(furthest, max_advance_steps[i] + i);
    if(furthest == i && furthest != max_advance_steps.size()-1) return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"max_advance_steps"};
  return GenericTestMain(args, "advance_by_offsets.cc",
                         "advance_by_offsets.tsv", &CanReachEnd,
                         DefaultComparator{}, param_names);
}
