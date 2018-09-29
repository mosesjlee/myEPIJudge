#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
vector<int> Multiply(vector<int> num1, vector<int> num2) {

  if(num1.size() == 1 && num1[0] == 0) return num1;
  if(num2.size() == 1 && num2[0] == 0) return num2;

  // TODO - you fill in here.
  vector<int> result(num1.size() + num2.size(), 0);
  int sign = 1;
  if(num2[0] < 0 ^ num1[0] < 0) {
    sign = -1;
  }

  num1[0] = abs(num1[0]);
  num2[0] = abs(num2[0]);

  int start_from = 2;
  for(int i = num1.size()-1; i >= 0; i--) {
    int curr_result = result.size()-start_from;
    for(int j = num2.size()-1; j >= 0; j--) {
      result[curr_result+1] += num1[i] * num2[j];
      result[curr_result] += result[curr_result+1]/10;
      result[curr_result+1] %= 10;
      curr_result--;
    }
    start_from++;
  }

  auto it = result.begin();
  while(*it == 0) {
    result.erase(it); //Erase removes from the spot then scoots everything over. so you don't need to increment iterator
  }

  result[0] *= sign;
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num1", "num2"};
  return GenericTestMain(args, "int_as_array_multiply.cc",
                         "int_as_array_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
