#include <string>
#include <unordered_map>
#include <unordered_set>
#include "test_framework/generic_test.h"
using std::string;
//#define MY_ATTEMPT
bool CanFormPalindrome(const string& s) {
  // TODO - you fill in here.
#ifdef MY_ATTEMPT
#pragma message("MY ATTEMPT")
  std::unordered_map<char, int> letter_count;
  for(char c : s) {
    letter_count[c]++;
  }

  int odd_letter_count = 0;
  for(std::pair<char, int> letter : letter_count) {
   if(letter.second%2 != 0) {
      odd_letter_count++;
    }
  }

  return odd_letter_count <= 1;
#elif defined BOOK_ATTEMPT
#pragma message("BOOK ATTEMPT")
  std::unordered_set<char> char_counter;
  for(char c : s) {
    if(char_counter.count(c)) {
      char_counter.erase(c);
    }
    else {
      char_counter.insert(c);
    }
  }

  return char_counter.size() <= 1;
#else //If i had a better idea

#endif
  
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_permutable_to_palindrome.cc",
                         "is_string_permutable_to_palindrome.tsv",
                         &CanFormPalindrome, DefaultComparator{}, param_names);
}
