#include <istream>
#include <string>
#include <vector>
#include <unordered_set>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
//#define BRUTE_FORCE
#define MY_OPT_ATTEMPT
typedef enum { kWhite, kBlack } Color;
struct Coordinate {
  bool operator==(const Coordinate& that) const {
    return x == that.x && y == that.y;
  }

  int x, y;
};

void SearchMazeHelper(vector<vector<Color>> & maze, 
                      const Coordinate& s, const Coordinate& e, 
                              vector<vector<bool>> * visited, 
                              vector<Coordinate> * path);


void SearchMazeHelper2(vector<vector<Color>> * maze, 
                       const Coordinate& s, const Coordinate& e, 
                        vector<Coordinate> * path);

bool SearchMazeHelperBook(vector<vector<Color>> * maze_ptr, 
                       const Coordinate& s, const Coordinate& e, 
                        vector<Coordinate> * path_ptr);

vector<Coordinate> SearchMaze(vector<vector<Color>> maze, const Coordinate& s,
                              const Coordinate& e) {
  // TODO - you fill in here.
#ifdef BRUTE_FORCE
#pragma message ("BRUTE_FORCE")
  vector<bool> list_visited(maze[0].size(), false);
  vector<vector<bool>> visited (maze.size(), list_visited);
  vector<Coordinate> path;
  SearchMazeHelper(maze, s, e, &visited, &path);
  return {path.rbegin(), path.rend()};

#elif defined MY_OPT_ATTEMPT
#pragma message ("MY_OPT_ATTEMPT")
  vector<Coordinate> path;
  SearchMazeHelper2(&maze, s, e, &path);
  return {path.rbegin(), path.rend()};
#else
#pragma message ("BOOK OPTIMIZED")
  vector<Coordinate> path;
  SearchMazeHelperBook(&maze, s, e, &path);
  return path;
#endif
}

void SearchMazeHelper(vector<vector<Color>> & maze, 
                      const Coordinate& s, const Coordinate& e, 
                      vector<vector<bool>> * visited, 
                      vector<Coordinate> * path) {
  if(s == e) {
    path->push_back(s);
    return;
  }

  (*visited)[s.x][s.y] = true;
  vector<Coordinate> neighbors = {{s.x, s.y+1},
                                  {s.x, s.y-1},
                                  {s.x-1, s.y},
                                  {s.x+1, s.y}};

  for(Coordinate c : neighbors) {
    if((c.x < maze.size() && c.x > -1) && (c.y < maze[c.x].size() && c.y > -1)) {
      if(maze[c.x][c.y] != kBlack && !(*visited)[c.x][c.y]) {
        SearchMazeHelper(maze, c, e, visited, path);
      }

      if(path->size() > 0 && path->front() == e) {
        path->push_back(s);
        break;
      }
    }
  }
}

void SearchMazeHelper2(vector<vector<Color>> * maze, 
                       const Coordinate& s, const Coordinate& e, 
                        vector<Coordinate> * path) {
  if(s == e) {
    path->push_back(s);
    return;
  }

  (*maze)[s.x][s.y] = kBlack;

  vector<Coordinate> neighbors = {{s.x, s.y+1},
                                  {s.x, s.y-1},
                                  {s.x-1, s.y},
                                  {s.x+1, s.y}};

  for(Coordinate c : neighbors) {
    if(c.x > -1 && (c.x < maze->size()) && (c.y > -1 && c.y < (*maze)[c.x].size())) {
      if((*maze)[c.x][c.y] != kBlack) {
        SearchMazeHelper2(maze, c, e, path);
      }

      if(path->size() > 0) {
        path->push_back(s);
        break;
      }
    }
  }
}

bool SearchMazeHelperBook(vector<vector<Color>> * maze_ptr, 
                       const Coordinate& cur, const Coordinate& e, 
                        vector<Coordinate> * path_ptr) {
  auto & maze = *maze_ptr;
  if(cur.x < 0 || cur.x >= maze.size() || cur.y < 0 || cur.y >= maze[cur.x].size() || maze[cur.x][cur.y] != kWhite) {
    return false;
  }

  auto & path = *path_ptr;
  path.emplace_back(cur);
  maze[cur.x][cur.y] = kBlack;
  if(cur == e) return true;

  vector<Coordinate> neighbors = {{cur.x, cur.y+1},
                                {cur.x, cur.y-1},
                                {cur.x-1, cur.y},
                                {cur.x+1, cur.y}};
  for(Coordinate & c : neighbors) {
    if(SearchMazeHelperBook(maze_ptr, c, e, path_ptr)) {
      return true;
    }
  }

  path.pop_back();
  return false;
}

template <>
struct SerializationTraits<Color> : SerializationTraits<int> {
  using serialization_type = Color;

  static serialization_type Parse(const std::string& str) {
    return static_cast<serialization_type>(
        SerializationTraits<int>::Parse(str));
  }

  static serialization_type JsonParse(const json_parser::Json& json_object) {
    return static_cast<serialization_type>(
        SerializationTraits<int>::JsonParse(json_object));
  }
};

template <>
struct SerializationTraits<Coordinate> : UserSerTraits<Coordinate, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
    return {};
  }

  static std::vector<int> GetMetrics(const Coordinate& x) { return {}; }
};

bool PathElementIsFeasible(const vector<vector<Color>>& maze,
                           const Coordinate& prev, const Coordinate& cur) {
  if (!(0 <= cur.x && cur.x < maze.size() && 0 <= cur.y &&
        cur.y < maze[cur.x].size() && maze[cur.x][cur.y] == kWhite)) {
    return false;
  }
  return cur == Coordinate{prev.x + 1, prev.y} ||
         cur == Coordinate{prev.x - 1, prev.y} ||
         cur == Coordinate{prev.x, prev.y + 1} ||
         cur == Coordinate{prev.x, prev.y - 1};
}

bool SearchMazeWrapper(TimedExecutor& executor,
                       const vector<vector<Color>>& maze, const Coordinate& s,
                       const Coordinate& e) {
  vector<vector<Color>> copy = maze;

  auto path = executor.Run([&] { return SearchMaze(copy, s, e); });

  if (path.empty()) {
    return s == e;
  }

  if (!(path.front() == s) || !(path.back() == e)) {
    throw TestFailure("Path doesn't lay between start and end points");
  }

  for (size_t i = 1; i < path.size(); i++) {
    if (!PathElementIsFeasible(maze, path[i - 1], path[i])) {
      throw TestFailure("Path contains invalid segments");
    }
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "maze", "s", "e"};
  return GenericTestMain(args, "search_maze.cc", "search_maze.tsv",
                         &SearchMazeWrapper, DefaultComparator{}, param_names);
}
