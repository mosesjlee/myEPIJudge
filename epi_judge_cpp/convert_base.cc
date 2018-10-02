#include <string>
#include "test_framework/generic_test.h"
using std::string;
using std::vector;
#define BRUTE_FORCE
string ConvertBase(const string& num_as_string, int b1, int b2) {
  // TODO - you fill in here.
#ifdef BRUTE_FORCE
  if(num_as_string == "0" || num_as_string == "-0") return num_as_string;
  long copy_num = 0;
  int hex_num_start = 'A' - 10;
  int power = 0;
  string retval = "";

  for(int i = (num_as_string[0] == '-'); i < num_as_string.length(); i++) {
    copy_num *= b1;
    if(isalpha(num_as_string[i])) {
      copy_num += num_as_string[i] - hex_num_start;
    }
    else {
      copy_num += num_as_string[i] - '0';
    }
  }

  power = ceil(log10(copy_num)/log10(b2));
  vector<int> places(power+1, 0);

  while(copy_num >= b2) {
    long curr_chunk = pow(b2, power);
    if(curr_chunk > copy_num) {
      power--;
    }
    else {
      copy_num -= curr_chunk;
      places[power]++;
    }
  }

  for(int i = places.size()-1; i >= 0; i--) {
    if(places[i] < 10) {
      retval.push_back(places[i] + '0');
    }
    else {
      retval.push_back(places[i] + hex_num_start);
    }
  }

  if(copy_num != 0) {
    if(copy_num < 10) {
      retval[retval.length()-1] = copy_num + '0';
    }
    else {
      retval[retval.length()-1] = copy_num + hex_num_start;
    }
  }
  
  if(retval[0] == '0') retval = retval.erase(0, 1);
  if(num_as_string[0] == '-') retval = "-" + retval;
  return retval;
#endif
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
