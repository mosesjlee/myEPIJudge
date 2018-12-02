#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

vector<double> OnlineMedian(vector<int>::const_iterator sequence_begin,
                            const vector<int>::const_iterator& sequence_end) {
  // TODO - you fill in here.
  std::priority_queue<double, std::vector<double>, std::greater<double>> min_heap;
  std::priority_queue<double> max_heap;
  vector<double> retval;
  double curr_median = 0.0;
  while(sequence_begin != sequence_end) {
    double curr_val = *sequence_begin++;
    if(curr_val >= curr_median) {
      min_heap.push(curr_val);
    }
    else {
      max_heap.push(curr_val);
    }

    if(fabs(max_heap.size()-min_heap.size()) > 1) {
      if(max_heap.size() > min_heap.size()) {
        min_heap.push(max_heap.top());
        max_heap.pop();
      }
      else {
        max_heap.push(min_heap.top());
        min_heap.pop();
      }
    }

    if(max_heap.size() == min_heap.size()) {
      curr_median = (max_heap.top() + min_heap.top())/2.0;
    }
    else if(max_heap.size() > min_heap.size()) {
      curr_median = max_heap.top();
    }
    else {
      curr_median = min_heap.top();
    }
    retval.push_back(curr_median);
  }

  return retval;
}
vector<double> OnlineMedianWrapper(const vector<int>& sequence) {
  return OnlineMedian(cbegin(sequence), cend(sequence));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence"};
  return GenericTestMain(args, "online_median.cc", "online_median.tsv",
                         &OnlineMedianWrapper, DefaultComparator{},
                         param_names);
}
