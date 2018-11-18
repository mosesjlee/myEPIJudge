#include <string>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
  // TODO - you fill in here.
#ifdef FIRST_ATTEMPT
  if(x == 0) return "0";
  long copy_x = abs(static_cast<long>(x)); //To prevent integer overflow
  
  string retval = "";
  while(copy_x) {
    char temp = copy_x%10 + '0';
    retval = temp + retval;
    copy_x/= 10;
  }

  if(x < 0) retval = "-" + retval;
  return retval;
#else
  bool is_negative = x < 0;
  string retval = "";

  do {
    retval += (abs(x%10) + '0');
    x /= 10;
  } while(x);
  
  if(is_negative) retval += '-';
  return {retval.rbegin(), retval.rend()};
#endif
}

int StringToInt(const string& s) {
  // TODO - you fill in here.
  long retval = 0;    //Long to prevent integer overflow

  for(int i = (int) (s[0] == '-'); i < s.length(); i++) {
    retval *= 10;
    retval += (s[i] - '0');  
  }

  return retval * (s[0] == '-' ? -1 : 1);
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
