#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
//#define BRUTE_FORCE

int GetCombo(const vector<int>& scores, const int total, int i, vector<vector<int>> & mem);

int NumCombinationsForFinalScore(int final_score,
                                 const vector<int>& individual_play_scores) {
  // TODO - you fill in here.
#ifdef BRUTE_FORCE
#pragma message("BRUTE FORCE")  
  vector<int> inner(final_score+1, 0);
  vector<vector<int>> mem(individual_play_scores.size(), inner);
  return GetCombo(individual_play_scores, final_score, individual_play_scores.size()-1, mem);
#else
#pragma message("BOOK OPTIMIZED")
  vector<int> inner(final_score+1, 0);
  vector<vector<int>> mem(individual_play_scores.size(), inner);
  for(int i = 0; i < individual_play_scores.size(); i++) {
    mem[i][0] = 1;
    for(int j = 1; j <= final_score; j++) {
      int without_this_play = 0;
      if(i >= 1) without_this_play = mem[i-1][j];

      int with_this_play = 0;
      if(j >= individual_play_scores[i]) {
        with_this_play = mem[i][j-individual_play_scores[i]];
      }

      mem[i][j] = without_this_play + with_this_play;
    }
  }

  return mem.back().back();
#endif
}

int GetCombo(const vector<int>& scores, const int total, int i, vector<vector<int>> & mem) {
  if(i >= 0 && mem[i][total] != 0)
    return mem[i][total];

  if(total < 0 || i < 0) return 0;

  int retval = 0;
  
  if(total == 0) retval = 1;
  else if(total < scores[i]) {
    retval = GetCombo(scores, total, i-1, mem);
  }
  else {
    retval = GetCombo(scores,total-scores[i], i, mem) + GetCombo(scores, total, i-1, mem);
  }
  
  mem[i][total] = retval;
  return retval;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"final_score", "individual_play_scores"};
  return GenericTestMain(args, "number_of_score_combinations.cc",
                         "number_of_score_combinations.tsv",
                         &NumCombinationsForFinalScore, DefaultComparator{},
                         param_names);
}
