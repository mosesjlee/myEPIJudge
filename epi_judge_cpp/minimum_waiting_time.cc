#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

int MinimumTotalWaitingTime(vector<int> service_times) {
  // TODO - you fill in here.
  sort(service_times.begin(), service_times.end());

  int total_time = 0;
  int prev_wait = 0;
  int curr_wait = 0;
  for(int i = 1; i < service_times.size(); i++) {
    curr_wait = service_times[i-1] + prev_wait;
    total_time += curr_wait;
    prev_wait = curr_wait;
  }

  return total_time;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"service_times"};
  return GenericTestMain(args, "minimum_waiting_time.cc",
                         "minimum_waiting_time.tsv", &MinimumTotalWaitingTime,
                         DefaultComparator{}, param_names);
}
