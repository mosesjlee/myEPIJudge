#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
bool CanReachEnd(const vector<int>& max_advance_steps) {
	int curr_furthest = 0;
	for(int i = 0; i < max_advance_steps.size(); i++) {
		if(i + max_advance_steps[i] > curr_furthest) curr_furthest = i + max_advance_steps[i];
		if(curr_furthest <= i && i + max_advance_steps[i] < max_advance_steps.size()-1) return false;
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
