#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
#define O_N_SPACE
void RotateMatrix(vector<vector<int>>* square_matrix_ptr) {
  // TODO - you fill in here.
  vector<vector<int>> & matrix = *square_matrix_ptr;
  int length = matrix.size();
#ifdef O_N_SPACE
  vector<vector<int>> matrix_copy(matrix);
  for(int i = 0; i < length; i++){
    for(int j = length-1; j >= 0; j--) {
      matrix[i][(length-1)-j] = matrix_copy[j][i];
    }
  }
#else
    for(int i = 0; i < length; i++){
    for(int j = length-1; j >= 0; j--) {
      matrix[i][(length-1)-j] = matrix_copy[j][i];
    }
  }
#endif
  return;
}
vector<vector<int>> RotateMatrixWrapper(vector<vector<int>> square_matrix) {
  RotateMatrix(&square_matrix);
  return square_matrix;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "matrix_rotation.cc", "matrix_rotation.tsv",
                         &RotateMatrixWrapper, DefaultComparator{},
                         param_names);
}
