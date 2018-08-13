#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
vector<int> PlusOne(vector<int> A) {
  // TODO - you fill in here.
	vector<int> new_number(A);
	vector<int>::reverse_iterator end = new_number.rbegin();
	
	++(*end);

	for(;end != new_number.rend()-1 && *end >= 10; end++) {
		*end = *end%10;
		*(end+1) = *(end+1) += 1;
	}

	if(*end == 10 ) {
		new_number[0] = 1;
		new_number.emplace_back(0);
	}

  return new_number;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "int_as_array_increment.cc",
                         "int_as_array_increment.tsv", &PlusOne,
                         DefaultComparator{}, param_names);
}
