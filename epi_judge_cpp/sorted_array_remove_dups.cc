#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::vector;
// Returns the number of valid entries after deletion.
int DeleteDuplicates(vector<int>* A_ptr) {
  // TODO - you fill in here.
  if(A_ptr->size() == 0) return 0;

  int prev_num = A_ptr->front();
  vector<int> single_entry; single_entry.push_back(prev_num);
  for(int i = 1; i < A_ptr->size(); i++) {
    if(prev_num != A_ptr->at(i)) {
      single_entry.push_back(A_ptr->at(i));
    }
    prev_num = A_ptr->at(i);
  }

  A_ptr->clear();
  A_ptr->insert(A_ptr->begin(),single_entry.begin(), single_entry.end());

  return A_ptr->size();
}
vector<int> DeleteDuplicatesWrapper(TimedExecutor& executor, vector<int> A) {
  int end = executor.Run([&] { return DeleteDuplicates(&A); });
  A.resize(end);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A"};
  return GenericTestMain(
      args, "sorted_array_remove_dups.cc", "sorted_array_remove_dups.tsv",
      &DeleteDuplicatesWrapper, DefaultComparator{}, param_names);
}
