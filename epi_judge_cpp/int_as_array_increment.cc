#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
vector<int> PlusOne(vector<int> A) {
  // TODO - you fill in here.
  vector<int> added(A);
  added.back()++;
#ifdef MY_INITIAL_APPROACH
  int carry_over = 0;
  for(int i = added.size()-1; i >= 0; i --) {
    added[i] += carry_over;
    carry_over = added[i]/10;
    if(carry_over == 0) break;
    added[i] = 0;
  }

  if(carry_over == 1) added.emplace(added.begin(), carry_over);
#else
  //Why process the first element for carry_over?
  //Skip to the second least significant digit
  for(int i = added.size()-2; i >= 0; i--) {
    added[i] += added[i+1]/10;
    added[i+1] %= 10;
  }

  if(added[0] == 10) {
    added[0] = 0;
    added.emplace(added.begin(), 1);
  }
#endif
  return added;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "int_as_array_increment.cc",
                         "int_as_array_increment.tsv", &PlusOne,
                         DefaultComparator{}, param_names);
}
