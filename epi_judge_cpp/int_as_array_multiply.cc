#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
vector<int> Multiply(vector<int> num1, vector<int> num2) {
  // TODO - you fill in here.
	vector<int> temp_array;
	vector<int> final_array;

	//0 case
	if(num1.size() == 1 && num1[0] == 0) return num1;
	if(num2.size() == 1 && num2[0] == 0) return num2;

	//1 case
	if(num1.size() == 1 && num1[0] == 1) return num2;
	if(num2.size() == 1 && num2[0] == 1) return num1;

	bool is_negative = num1[0] < 0 ^ num2[0] < 0;
	
	num1[0] = abs(num1[0]);
	num2[0] = abs(num2[0]);

	final_array.assign(num1.size()+num2.size(), 0);
	
	for(int i = num1.size()-1; i >= 0; i--) {
		for(int j = num2.size()-1; j >= 0; j--) {
			final_array[i+j+1] += num1[i] * num2[j];
			final_array[i+j] += final_array[i+j+1]/10;
			final_array[i+j+1] %=10;
		}
	}

	auto it = final_array.begin();
	while(it != final_array.end()) {
		if(*it != 0) break;
		it++;
	}
	
	final_array = vector<int>(it, final_array.end());

	if(is_negative) {
		final_array[0] = -final_array[0];
	}

  return final_array;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num1", "num2"};
  return GenericTestMain(args, "int_as_array_multiply.cc",
                         "int_as_array_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
