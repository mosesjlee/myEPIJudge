#include <string>
#include "test_framework/generic_test.h"
using std::string;
using std::cout;
using std::endl;
#define FIRST_ATTEMPT
string LookAndSay(int n) {
  // TODO - you fill in here.
#ifdef FIRST_ATTEMPT
  string retval = "1";
  n--;
  while(n) {
    int char_count = 1;
    char curr_char = retval[0];
    string temp = "";
    for(int i = 1; i < retval.size(); i++) {
      if(curr_char == retval[i]) {
        char_count++;
      }
      else {
        temp += char_count+'0';
        temp += curr_char;
        curr_char = retval[i];
        char_count = 1;
      }
    }
    
    temp += char_count+'0';
    temp += curr_char;
    retval = temp;
    n--;
  }

  return retval;
#else
#endif
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "look_and_say.cc", "look_and_say.tsv",
                         &LookAndSay, DefaultComparator{}, param_names);
}
