#include <string>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;

void ReverseWords(string* s) {
  // TODO - you fill in here.
  if(s->length() == 1 || s->length() == 0) return;
  string & reverse_copy = *s;
  
  //Reverse the whole string
  reverse(reverse_copy.begin(), reverse_copy.end());
  
  int first_space = 0;
  int start = 0;
  while((first_space = reverse_copy.find_first_of(' ', start)) != string::npos) {
    reverse(reverse_copy.begin()+start, reverse_copy.begin()+first_space);
    start = first_space+1;
  }
  reverse(reverse_copy.begin()+start, reverse_copy.end());
  return;
}
string ReverseWordsWrapper(TimedExecutor& executor, string s) {
  string s_copy = s;

  executor.Run([&] { ReverseWords(&s_copy); });

  return s_copy;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "s"};
  return GenericTestMain(args, "reverse_words.cc", "reverse_words.tsv",
                         &ReverseWordsWrapper, DefaultComparator{},
                         param_names);
}
