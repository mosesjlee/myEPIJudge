#include <string>
#include "test_framework/generic_test.h"
using std::string;

int SSDecodeColID(const string& col) {
  // TODO - you fill in here.
  long retval = 0;

  for(int i = 0; i < col.length(); i++) {
    retval *= 26;
    retval += col[i] - 'A' + 1;
  }

  return retval;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"col"};
  return GenericTestMain(args, "spreadsheet_encoding.cc",
                         "spreadsheet_encoding.tsv", &SSDecodeColID,
                         DefaultComparator{}, param_names);
}
