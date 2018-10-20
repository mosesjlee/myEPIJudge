#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

void MergeTwoSortedArrays(vector<int>& A, int m, const vector<int>& B, int n) {
  // TODO - you fill in here.
  int last_idx = m + n - 1;
  int m_copy = m-1;
  int n_copy = n-1;

  while(m_copy > -1 && n_copy > -1) {
    if(A[m_copy] > B[n_copy]) {
      A[last_idx--] = A[m_copy--];
    }
    else {
      A[last_idx--] = B[n_copy--];
    }
  }

  //Copy the rest of B array because
  //we iterated through all of A
  while(n_copy > -1) {
    A[last_idx--] = B[n_copy--];
  }

  return;
}
vector<int> MergeTwoSortedArraysWrapper(vector<int> A, int m,
                                        const vector<int>& B, int n) {
  MergeTwoSortedArrays(A, m, B, n);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "m", "B", "n"};
  return GenericTestMain(
      args, "two_sorted_arrays_merge.cc", "two_sorted_arrays_merge.tsv",
      &MergeTwoSortedArraysWrapper, DefaultComparator{}, param_names);
}
