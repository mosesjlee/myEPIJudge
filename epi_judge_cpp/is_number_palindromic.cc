#include "test_framework/generic_test.h"
bool IsPalindromeNumber(int x) {
  if(x <= 0) return x == 0;

  long places = 0;
  double floored = floor(log10(x)); //Use log10 to get number of 10's places
  places = pow(10, floored);
  places = places == 0 ? 1 : places;

  while(places > 1) {
    long lsd = x % 10;
    long msd = x / places;
    if(lsd != msd)
      return false;

    x /= 10;
    x %= (places/10);
    places /= 100;
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "is_number_palindromic.cc",
                         "is_number_palindromic.tsv", &IsPalindromeNumber,
                         DefaultComparator{}, param_names);
}
