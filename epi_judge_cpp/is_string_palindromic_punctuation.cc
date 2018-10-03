#include <string>
#include "test_framework/generic_test.h"
using std::string;

bool IsPalindrome(const string& s) {
  // TODO - you fill in here.
  if(s.length() == 0) return true;

  int start = 0;
  int end = s.length()-1;

  do {
    while(!isalnum(s[start]) && start < end)
      start++;

    while(!isalnum(s[end]) && end > start)
      end--;

    if(tolower(s[start++]) != tolower(s[end--]))
      return false;

  } while (start < end);

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_palindromic_punctuation.cc",
                         "is_string_palindromic_punctuation.tsv", &IsPalindrome,
                         DefaultComparator{}, param_names);
}
