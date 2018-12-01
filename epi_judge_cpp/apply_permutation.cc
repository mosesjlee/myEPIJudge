#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
using std::cout;
using std::endl;
#define BRUTE_FORCE

void ApplyPermutation(vector<int>* perm_ptr, vector<int>* A_ptr) {
  // TODO - you fill in here.
  vector<int> & perm = *perm_ptr;
  vector<int> & A = *A_ptr;
#ifdef BRUTE_FORCE
  vector<int> results(A.size(), 0);
  for(int i = 0; i < perm.size(); i++) {
    results[perm[i]] = A[i];
  }

  for(int i = 0; i < A.size();i++) {
    A[i] = results[i];
  }
#else

#endif
  return;
}
vector<int> ApplyPermutationWrapper(vector<int> perm, vector<int> A) {
  ApplyPermutation(&perm, &A);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"perm", "A"};
  return GenericTestMain(args, "apply_permutation.cc", "apply_permutation.tsv",
                         &ApplyPermutationWrapper, DefaultComparator{},
                         param_names);
}
