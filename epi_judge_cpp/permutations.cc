#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

// #define BRUTE_FORCE
// #define PRINT_RESULTS

void PermutationsHelperBruteForceIdea(int n, vector<int> values,vector<int> * temp, vector<vector<int>> * results);
void PermutationsHelper(int n, vector<int> & values, vector<vector<int>> * results);

vector<vector<int>> Permutations(vector<int> A) {
  // TODO - you fill in here.
  vector<vector<int>> retval;
#ifdef BRUTE_FORCE
#pragma message("BRUTE FORCE")
  vector<int> temp;
  PermutationsHelperBruteForceIdea(A.size(), A, &temp, &retval);
#else
#pragma message("OPTIMIZED FORCE")
  PermutationsHelper(0, A, &retval);
#endif
#ifdef PRINT_RESULTS
  std::cout << std::endl;
  for(vector<int> line : retval) {
    std::cout << "[ ";
    for(int num : line) {
      std::cout << num << " ";
    }
    std::cout << "]"<<std::endl;
  }
#endif
  return retval;
}

void PermutationsHelper(int n, vector<int> & values, vector<vector<int>> * results) {
  if(n == values.size()) {
    results->emplace_back(values);
  }
  else {
    for(int i = n; i < values.size(); i++) {
      std::swap(values[i], values[n]);
      PermutationsHelper(n+1, values, results);
      std::swap(values[i], values[n]);
    }
  }
}

vector<int> RemoveElement(int elem, vector<int> A) {
  for(int i = 0; i < A.size();i++) {
    if(A[i] == elem) {
      A.erase(A.begin()+i);
      return A;
    }
  }
  return A;
}

void PermutationsHelperBruteForceIdea(int n, vector<int> values, vector<int> * temp, vector<vector<int>> * results) {
  if(temp->size() == n) {
    results->emplace_back(*temp);
  }
  else {
    for(int i = 0; i < values.size(); i++) {
      temp->push_back(values[i]);
      auto subset = RemoveElement(values[i], values);
      PermutationsHelperBruteForceIdea(n, subset, temp, results);
      temp->pop_back();
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(
      args, "permutations.cc", "permutations.tsv", &Permutations,
      &UnorderedComparator<vector<vector<int>>>, param_names);
}
