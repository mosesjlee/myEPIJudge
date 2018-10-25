#include <deque>
#include <vector>
#include <queue>
#include <utility>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::deque;
using std::vector;
//#define BRUTE_FORCE
void FlipColorHelper(int x, int y, vector<deque<bool>>* image_ptr, vector<deque<bool>>* orig_image_ptr, bool & orig);

void FlipColor(int x, int y, vector<deque<bool>>* image_ptr) {
  // TODO - you fill in here.
#ifdef BRUTE_FORCE
#pragma message("BRUTE FORCE USES DFS")
  //Uses DFS
  bool orig_val = (*image_ptr)[x][y];
  vector<deque<bool>> copy_image(*image_ptr);
  FlipColorHelper(x, y, image_ptr, &copy_image, orig_val);
  return;
#else
#pragma message("OPTIMIZED USES BFS")

  std::queue<std::pair<int, int>> pair_queue;
  pair_queue.emplace(std::pair<int, int>(x, y));
  auto & image = *image_ptr;
  bool color = image[x][y];

  while(!pair_queue.empty()) {
    auto curr_point = pair_queue.front();
    vector<std::pair<int, int>> neighbors = {std::pair<int, int>(curr_point.first, curr_point.second + 1),
                                             std::pair<int, int>(curr_point.first, curr_point.second - 1),
                                             std::pair<int, int>(curr_point.first + 1, curr_point.second),
                                             std::pair<int, int>(curr_point.first - 1, curr_point.second)};

    for(std::pair<int, int> next : neighbors) {
      if(next.first < 0 || next.first >= image.size() || 
        next.second < 0 || next.second >= image[next.first].size() || 
        image[next.first][next.second] != color) {
        continue;
      }
      else {
        pair_queue.emplace(next);
      }
    }

    image[curr_point.first][curr_point.second] = !color;
    pair_queue.pop();
  }
#endif
}

struct Point {
  int x, y;
};

void FlipColorHelper(int x, int y, vector<deque<bool>>* image_ptr, vector<deque<bool>>* orig_image_ptr, bool & orig){
  auto & copy_image = *orig_image_ptr;
  auto & image = *image_ptr;
  // std::cout << "x " << x << " y " << y << std::endl;
  if(x < 0 || x >= copy_image.size() || y < 0 || y >= copy_image[x].size() ||
     copy_image[x][y] != orig || image[x][y] != orig) {
    return;
  }

  image[x][y] = !orig;
  vector<Point> neighbors = {{x, y+1}, {x, y-1}, {x-1, y}, {x+1,y}};

  for(Point p : neighbors) {
    FlipColorHelper(p.x, p.y, image_ptr, orig_image_ptr,orig);
  }

}
vector<vector<int>> FlipColorWrapper(TimedExecutor& executor, int x, int y,
                                     vector<vector<int>> image) {
  vector<deque<bool>> b;
  b.reserve(image.size());
  for (const vector<int>& row : image) {
    deque<bool> tmp;
    tmp.resize(row.size());
    for (int i = 0; i < row.size(); ++i) {
      tmp[i] = static_cast<bool>(row[i]);
    }
    b.push_back(tmp);
  }

  executor.Run([&] { FlipColor(x, y, &b); });

  image.resize(b.size());

  for (int i = 0; i < image.size(); ++i) {
    image[i].resize(b.size());
    for (int j = 0; j < image[i].size(); ++j) {
      image[i][j] = b[i][j];
    }
  }
  return image;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "x", "y", "image"};
  return GenericTestMain(args, "matrix_connected_regions.cc", "painting.tsv",
                         &FlipColorWrapper, DefaultComparator{}, param_names);
}
