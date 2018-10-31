#include <algorithm>
#include <iterator>
#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

void NQueensHelper(int curr_queen, int n, vector<int> * temp, vector<vector<int>> * queen_placements);

vector<vector<int>> NQueens(int n) {
  // TODO - you fill in here.
  vector<vector<int>> retval;
  vector<int> results;
  NQueensHelper(0, n, &results, &retval);
  return retval;
}

bool IsSafeFromOtherQueens(vector<int> & queen_placements) {
  int col_id = queen_placements.size()-1;
  for(int i = 0; i < col_id; i++) {
    
    if(queen_placements[i] == queen_placements[col_id]) {
      return false;
    }
    
    int x_1 = i; int y_1 = queen_placements[i];
    int x_2 = col_id; int y_2 = queen_placements[col_id];
    int diff = abs(x_1 - x_2) - abs(y_1-y_2);
   
    if(diff == 0) {
      return false;
    }
  }


  return true;
}

void NQueensHelper(int curr_queen, int n_queen, vector<int> * temp, vector<vector<int>> * queen_placements) {
  if(n_queen == curr_queen) {
    queen_placements->emplace_back(*temp);
    return;
  }

  for(int i = 0; i < n_queen; i++) {
    temp->push_back(i);
    if(IsSafeFromOtherQueens(*temp)) {
      NQueensHelper(curr_queen+1, n_queen, temp, queen_placements);
    }

    temp->pop_back();
  }
}

bool Comp(vector<vector<int>>& a, vector<vector<int>>& b) {
  std::sort(std::begin(a), std::end(a));
  std::sort(std::begin(b), std::end(b));
  return a == b;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "n_queens.cc", "n_queens.tsv", &NQueens, &Comp,
                         param_names);
}
