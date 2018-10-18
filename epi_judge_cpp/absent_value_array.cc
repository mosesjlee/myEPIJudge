#include <stdexcept>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::invalid_argument;
using std::vector;

int FindMissingElement(vector<int>::const_iterator stream_begin,
                       const vector<int>::const_iterator& stream_end) {
  // TODO - you fill in here.
  int retval = -1;
  auto iter = stream_begin;
  const int num_buckets = 1 << 16;
  vector<int> header_counter(num_buckets, 0);

  //Read and count all the values
  while(iter != stream_end) {
    int header = *iter >> 16;
    ++header_counter[header];
    ++iter;
  }

  const int full_count = 1 << 16;
  int missing_candidate = -1;
  for (int i = 0; i < header_counter.size(); i++) {
    if(header_counter[i] < full_count) {
      missing_candidate = i;
      break;
    }
  }

  //This can be a type bitset as well to conserve space 
  //or vector<bool>
  vector<bool> subnet_counter(num_buckets, 0);
  iter = stream_begin;
  while(iter != stream_end) {
    int header = *iter >> 16;
    if(header == missing_candidate) {
      subnet_counter[0x0000FFFF & *iter] = 1;
      ++iter;
    }
  }

  int missing_subnet;
  for(int i = 0; i < subnet_counter.size(); i++){
    if(subnet_counter[i] == 0) {
      missing_subnet = i;
      break;
    }
  }
  
  return (missing_candidate << 16) | missing_subnet;
}
int FindMissingElementWrapper(const vector<int>& stream) {
  try {
    return FindMissingElement(cbegin(stream), cend(stream));
  } catch (invalid_argument&) {
    throw TestFailure("Unexpected no_missing_element exception");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"stream"};
  return GenericTestMain(args, "absent_value_array.cc",
                         "absent_value_array.tsv", &FindMissingElementWrapper,
                         DefaultComparator{}, param_names);
}
