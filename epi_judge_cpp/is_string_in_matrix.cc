#include <vector>
#include <utility>
#include <tuple>
#include <unordered_set>
#include "test_framework/generic_test.h"


using std::get;
using std::hash;
using std::make_tuple;
using std::make_unique;
using std::tuple;
using std::unordered_set;
using std::vector;

#define BRUTE_FORCE
//#define PATTERN_HELPER_2
struct HashTuple {
  size_t operator()(const tuple<int, int, int>& t) const {
    return std::hash<int>()(get<0>(t) ^ get<1>(t) * 1021 ^ get<2>(t) * 1048573);
  }
};


bool PatternHelper(int row, int col, const vector<vector<int>>& grid, const vector<int>& pattern, int curr_idx);
bool PatternHelper2(int row, int col, const vector<vector<int>>& grid, const vector<int>& pattern, int curr_idx, vector<vector<int>>& visited);
bool PatternHelper3(int row, int col, const vector<vector<int>>& grid, 
                    const vector<int>& pattern, int curr_idx,unordered_set<tuple<int, int, int>, HashTuple>*);


bool IsPatternContainedInGrid(const vector<vector<int>>& grid,
                              const vector<int>& pattern) {
#ifdef BRUTE_FORCE
#pragma message("BRUTE FORCE")
  // TODO - you fill in here.
  vector<vector<int>> visited(grid);
  for(int row = 0; row < grid.size(); row++) {
    for(int col = 0; col < grid.front().size(); col++) {
      if(grid[row][col] == pattern.front()) {
#ifdef PATTERN_HELPER_2
#pragma message("PATTERN_HELPER_2")
        if(PatternHelper2(row, col, grid, pattern, 0, visited)) {
#else
#pragma message("PATTERN HELPER 1")
        if(PatternHelper(row, col, grid, pattern, 0)) {
#endif
          return true;
        }
      }
    }
  }
#else

#pragma message("BOOK OPTIMIZED")
  unordered_set<tuple<int, int, int>, HashTuple> visited;

  for(int row = 0; row < grid.size(); row++) {
    for(int col = 0; col < grid.front().size(); col++) {
      if(grid[row][col] == pattern.front()) {
        if(PatternHelper3(row, col, grid, pattern, 0, &visited)) {
          return true;
        }
      }
    }
  }
#endif
  return false;
}

bool PatternHelper(int row, int col, const vector<vector<int>>& grid, const vector<int>& pattern, int curr_idx) {
  if(grid[row][col] != pattern[curr_idx]) {
    return false;
  }

  if(curr_idx == pattern.size()-1) {
    return true;
  }

  vector<std::pair<int, int>> next_locs = {{row+1, col}, {row-1, col}, {row, col+1}, {row, col-1}};
  for(auto loc : next_locs) {
    if(loc.first >= 0 && loc.first < grid.size() && 
       loc.second >= 0 && loc.second < grid.front().size()) {
      if(PatternHelper(loc.first, loc.second, grid, pattern, curr_idx+1)) {
        return true;
      }
    }
  }

  return false;
}

bool PatternHelper2(int row, int col, const vector<vector<int>>& grid, const vector<int>& pattern, int curr_idx, vector<vector<int>>& visited) {
  if(grid[row][col] != pattern[curr_idx]) {
    return false;
  }

  if(curr_idx == pattern.size()-1) {
    return true;
  }

  int curr_visited = visited[row][col];
  visited[row][col] = -1;
  vector<std::pair<int, int>> next_locs = {{row+1, col}, {row-1, col}, {row, col+1}, {row, col-1}};
  for(auto loc : next_locs) {
    if(loc.first >= 0 && loc.first < grid.size() && 
       loc.second >= 0 && loc.second < grid.front().size() && visited[loc.first][loc.second] != -1) {
      if(PatternHelper(loc.first, loc.second, grid, pattern, curr_idx+1)) {
        return true;
      }
    }
  }
  visited[row][col] = curr_visited; // need to store visited and the current index
  return false;
}

bool PatternHelper3(int row, int col, const vector<vector<int>>& grid, const vector<int>& pattern, int curr_idx,unordered_set<tuple<int, int, int>, HashTuple>* visited) {

  if(grid[row][col] != pattern[curr_idx]) {
    visited->emplace(row, col, curr_idx);
    return false;
  }

  if(curr_idx == pattern.size()-1) {
    return true;
  }

  vector<std::pair<int, int>> next_locs = {{row+1, col}, {row-1, col}, {row, col+1}, {row, col-1}};
  for(auto loc : next_locs) {
    if(loc.first >= 0 && loc.first < grid.size() && 
       loc.second >= 0 && loc.second < grid.front().size() && visited->find(std::make_tuple(loc.first, loc.second, curr_idx+1)) == visited->end()) {
      if(PatternHelper(loc.first, loc.second, grid, pattern, curr_idx+1)) {
        return true;
      }
    }
  }

  visited->emplace(row, col, curr_idx); // need to store visited and the current index
  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"grid", "pattern"};
  return GenericTestMain(args, "is_string_in_matrix.cc",
                         "is_string_in_matrix.tsv", &IsPatternContainedInGrid,
                         DefaultComparator{}, param_names);
}
