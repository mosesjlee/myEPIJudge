#include "test_framework/generic_test.h"
#define OPTION_2
short Parity(unsigned long long x) {
  short result = 0;
#ifdef OPTION_1
  //Optimized to only get rid of lowest set bit
  while(x) {
    result ^= 1;
    x = x&(x-1);
  }
#elif defined OPTION_2
#pragma message("XOR Folding")
  //The folding option
  x ^= x >> 32;     
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  x ^= x >> 2;
  x ^= x >> 1;
  result = x & 1;
#else
  //BRUTE FORCE
  while(x) {
    result ^= x & 1;
    x >>= 1;
  }
#endif

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                         DefaultComparator{}, param_names);
}
