#include "test_framework/generic_test.h"
#define BRUTE_FORCE

int SquareRoot(int k) {
  // TODO - you fill in here.
#ifdef BRUTE_FORCE
#pragma message ("BRUTE FORCE")
  long upper_k = k;
  while(upper_k * upper_k > k) { 
    upper_k /=2;
  }
  while(upper_k * upper_k < k) {
    upper_k++;
  }

  if(upper_k * upper_k == k) return upper_k;

  return upper_k-1;
#else
#pragma message ("OPTIMIZE")  
  long left = 0, right = k;
  while(left <= right) {
    long mid = left + (right - left)/2; //This is the divide 2 part
    if(mid * mid > k) {
      right = mid - 1;
    }
    else {
      left = mid + 1;
    }
  }
  return left-1;
#endif
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "int_square_root.cc", "int_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
