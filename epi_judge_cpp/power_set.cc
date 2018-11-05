#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
void GeneratePowerSetHelper(int n, const vector<int>& input_set, vector<int> * temp, vector<vector<int>> * results);
vector<vector<int>> GeneratePowerSet(const vector<int>& input_set) {
  // TODO - you fill in here.
  vector<vector<int>> retval;
  vector<int> temp;
  GeneratePowerSetHelper(0, input_set, &temp, &retval);
  retval.push_back({});
  // std::cout << "\nsize of set " << input_set.size() << " size of power set " << retval.size() << std::endl;
  return retval;
}

void GeneratePowerSetHelper(int n, const vector<int>& input_set, vector<int> * temp,vector<vector<int>> * results) {
  if(n < input_set.size()) {
    for(int i = n; i < input_set.size(); i++) {
      temp->push_back(i);
      GeneratePowerSetHelper(i+1, input_set, temp, results);
      results->emplace_back(*temp);
      temp->pop_back();
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"input_set"};
  return GenericTestMain(
      args, "power_set.cc", "power_set.tsv", &GeneratePowerSet,
      &UnorderedComparator<vector<vector<int>>>, param_names);
}
