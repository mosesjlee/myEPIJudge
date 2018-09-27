#include "test_framework/generic_test.h"
long long Reverse(int x) {
  long copy = (long) x;
  long result = 0;
  while(copy) {
    long last_digit = copy % 10;
    copy /= 10;
    result = result * 10 + last_digit;
  }

  //Don't have to check for negative because modulus will return a negative answer
  //And the negative will propagate because of the multiplicative property
  //of negative and positive numbers
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_digits.cc", "reverse_digits.tsv",
                         &Reverse, DefaultComparator{}, param_names);
}
