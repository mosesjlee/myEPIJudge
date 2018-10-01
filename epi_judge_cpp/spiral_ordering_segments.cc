#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
vector<int> MatrixInSpiralOrder(vector<vector<int>> square_matrix) {
  // TODO - you fill in here.

  if(square_matrix.size() == 0) return {};
  vector<int> result;
  int differential = square_matrix.size()-1;
  int starting_corners = ceil(square_matrix.size()/2.0);

  // std::cout << " starting_corners ==> " << starting_corners << std::endl;

  for(int i = 0; i < starting_corners; i++) {
    result.emplace_back(square_matrix[i][i]);
    for(int j = i+1; j < differential; j++) {
      result.emplace_back(square_matrix[i][j]);
    }

    for(int j = i; j < differential; j++) {
      result.emplace_back(square_matrix[j][differential]);
    }

    for(int j = differential; j > i; j--) {
      result.emplace_back(square_matrix[differential][j]);
    }

    for(int j = differential; j > i; j--) {
      result.emplace_back(square_matrix[j][i]);
    }

    differential--;
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering_segments.cc",
                         "spiral_ordering_segments.tsv", &MatrixInSpiralOrder,
                         DefaultComparator{}, param_names);
}
