#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

vector<int> IntersectTwoSortedArrays(const vector<int>& A,
                                     const vector<int>& B) {
  // TODO - you fill in here.
  vector<int> retval;
  for(int a_idx = 0, b_idx = 0; a_idx < A.size() && b_idx < B.size();) {

    if(A[a_idx] < B[b_idx]) {
      a_idx++;
    }
    else if(B[b_idx] < A[a_idx]){
      b_idx++;
    }
    else if(A[a_idx] == B[b_idx]) {
      if(retval.empty() || A[a_idx] != retval.back()) {
        retval.push_back(A[a_idx]);
      }
      a_idx++; b_idx++;
    }
  }
  return retval;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(
      args, "intersect_sorted_arrays.cc", "intersect_sorted_arrays.tsv",
      &IntersectTwoSortedArrays, DefaultComparator{}, param_names);
}
