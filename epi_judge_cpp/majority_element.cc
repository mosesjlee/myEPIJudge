#include <string>
#include <vector>
#include "test_framework/generic_test.h"
#include <unordered_map>
using std::string;
using std::vector;
#define BRUTE_FORCE
string MajoritySearch(vector<string>::const_iterator stream_begin,
                      const vector<string>::const_iterator stream_end) {
  // TODO - you fill in here.
#ifdef BRUTE_FORCE
  std::unordered_map<string ,int> majority;
  while(stream_begin != stream_end) {
    majority[*stream_begin]++;
    stream_begin++;
  }

  int max = 0;
  string retval = "";
  for(auto pair : majority) {
    if(pair.second > max) {
      max = pair.second;
      retval = pair.first;
    }
  }
  return retval;
#else
  string retval = "";
  int count = 0;

  while(stream_begin != stream_end) {
    string it = *stream_begin++;
    if(count == 0) {
      retval = it;
      count++;
    }
    else if(retval == it) {
      count++;
    }
    else {
      count--;
    }
  }

  return retval;
#endif
}
string MajoritySearchWrapper(const vector<string>& stream) {
  return MajoritySearch(cbegin(stream), cend(stream));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"stream"};
  return GenericTestMain(args, "majority_element.cc", "majority_element.tsv",
                         &MajoritySearchWrapper, DefaultComparator{},
                         param_names);
}
