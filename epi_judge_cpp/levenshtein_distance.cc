#include <string>
#include <vector>
#include "test_framework/generic_test.h"
using std::string;
using std::vector;

int LevenshteinDistance(const string& A, const string& B) {
  // TODO - you fill in here.
  vector<int> b_v(B.length()+1, 0);
  vector<vector<int>> Matrix(A.length()+1, b_v);

  for(int i = 0; i <= B.length(); i++) {
    Matrix[0][i] = i;
  }

  for(int i = 0; i <= A.length(); i++) {
    Matrix[i][0] = i;
  }

  for(int row = 1; row <= A.length(); row++) {
    for(int col = 1; col <= B.length(); col++) {
      if(A[row-1] == B[col-1]) {
        Matrix[row][col] = Matrix[row-1][col-1];
      }
      else {
        int upper = Matrix[row-1][col]+1;
        int left = Matrix[row][col-1]+1;
        int diag = Matrix[row-1][col-1]+1;
        Matrix[row][col] = fmin(fmin(upper, left), diag);
      }
    }
  }

  return Matrix.back().back();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(args, "levenshtein_distance.cc",
                         "levenshtein_distance.tsv", &LevenshteinDistance,
                         DefaultComparator{}, param_names);
}
