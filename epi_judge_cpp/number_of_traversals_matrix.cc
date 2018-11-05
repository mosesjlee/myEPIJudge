#include "test_framework/generic_test.h"
#include <vector>
int NumberOfWays(int n, int m) {
  // TODO - you fill in here.
  std::vector<int> cols(n,0);
  std::vector<std::vector<int>> matrix(m, cols);

  for(int row = 0; row < m; row++) {
    for(int col = 0; col < n; col++) {
      if(row == 0 || col == 0) {
        matrix[row][col] = 1;
      }
      else {
        matrix[row][col] = matrix[row-1][col] + matrix[row][col-1];
      }
    }
  }

  return matrix.back().back();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "m"};
  return GenericTestMain(args, "number_of_traversals_matrix.cc",
                         "number_of_traversals_matrix.tsv", &NumberOfWays,
                         DefaultComparator{}, param_names);
}
