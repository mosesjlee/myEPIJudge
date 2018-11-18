#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
//#define BRUTE_FORCE
int SearchSmallest(const vector<int>& A) {
  // TODO - you fill in here.
  long left = 0, right = A.size()-1;
  long retval = 0;
#ifdef BRUTE_FORCE
#pragma message("BRUTE FORCE")  
  while(left <= right) {
    if(A[left] > A[right]) {
      left++; right--;
    }
    else {
      if(A[left] <= A[(right+1)%A.size()])
        retval = left;
      else 
        retval = (right+1)%A.size();
      break;
    }
  }

 if(left > right) retval = left;

#else
#pragma message("OPTIMIZED")
  while(left < right) {
    int mid = left + (right - left)/2;
    if(A[mid] > A[right]) {
      left = mid + 1;
    }
    else
      right = mid;
  }
  retval = left;
#endif
  return retval;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "search_shifted_sorted_array.cc",
                         "search_shifted_sorted_array.tsv", &SearchSmallest,
                         DefaultComparator{}, param_names);
}
