#include <string>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
  // TODO - you fill in here.
  if(x == 0) return "0";

  int curr_digit = 0;
  long copy_x = x;
  string retval = "";
  while(copy_x) {
    curr_digit = abs(copy_x % 10);
    retval.insert(0, 1,(char) ('0' + curr_digit));
    copy_x /= 10;
  }

  if(x < 0) {
    retval.insert(0, 1,'-');
  }

  return retval;
}

int StringToInt(const string& s) {
  // TODO - you fill in here.
  long multiplier = pow(10, s.size()-1);
  int retval = 0;
  
  if(s[0] == '-') multiplier /=10;

  for(int i = (s[0] == '-'); i < s.size(); i++) {
    retval += (s[i] - '0') * multiplier;
    multiplier /= 10;
  }

  if(s[0] == '-') retval *= -1;

  return retval;
}
void Wrapper(int x, const string& s) {
  if (IntToString(x) != s) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
