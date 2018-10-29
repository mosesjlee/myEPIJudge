#include <stdexcept>
#include <string>
#include <vector>
#include <utility>
#include <queue>
#include <unordered_set>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

void FillSurroundedRegions(vector<vector<char>>* board_ptr) {
  // TODO - you fill in here.
  auto & board = *board_ptr;
  std::vector<std::pair<int, int>> edge_points; 

  for(int i = 0; i < board.front().size(); i++) { 
    edge_points.push_back(std::pair<int, int>(0, i));
    edge_points.push_back(std::pair<int, int>(board.size()-1, i));  
  }

  for(int j = 0; j < board.size(); j++) {
    edge_points.push_back(std::pair<int, int>(j, 0));
    edge_points.push_back(std::pair<int, int>(j, board[j].size()-1));
  }

  std::queue<std::pair<int,int>> edge_queue;

  for(const auto & ep : edge_points) { 
    edge_queue.emplace(ep);
    while(!edge_queue.empty()) {
      auto next = edge_queue.front();
      edge_queue.pop();
      vector<std::pair<int, int>> neighbors = {std::pair<int, int>(next.first, next.second+1), 
                                               std::pair<int, int>(next.first, next.second-1), 
                                               std::pair<int, int>(next.first+1, next.second), 
                                               std::pair<int, int>(next.first-1, next.second)};

      if(next.first > -1 && next.first < board.size() && 
        next.second > -1 && next.second < board.front().size() &&
        board[next.first][next.second] == 'W') {
        board[next.first][next.second] = 'T';
        for(const auto & p : neighbors) {
          edge_queue.emplace(p);
        }
      }
    }
  }

  for(int i = 0; i < board.size(); i++) {
    for(int j = 0; j < board[i].size(); j++) {
      char c = board[i][j];
      board[i][j] = c != 'T' ? 'B' : 'W';
    }
  }

  return;
}

vector<vector<string>> FillSurroundedRegionsWrapper(
    TimedExecutor& executor, vector<vector<string>> board) {
  vector<vector<char>> char_vector;
  char_vector.resize(board.size());
  for (int i = 0; i < board.size(); i++) {
    for (const string& s : board[i]) {
      if (s.size() != 1) {
        throw std::runtime_error("String size is not 1");
      }
      char_vector[i].push_back(s[0]);
    }
  }

  executor.Run([&] { FillSurroundedRegions(&char_vector); });

  board.clear();
  board.resize(char_vector.size(), {});
  for (int i = 0; i < board.size(); i++) {
    for (char c : char_vector[i]) {
      board[i].emplace_back(1, c);
    }
  }

  return board;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "board"};
  return GenericTestMain(
      args, "matrix_enclosed_regions.cc", "matrix_enclosed_regions.tsv",
      &FillSurroundedRegionsWrapper, DefaultComparator{}, param_names);
}
