#include <deque>
#include <initializer_list>
#include <queue>
#include <utility>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"

using std::deque;
using std::initializer_list;
using std::make_pair;
using std::pair;
using std::queue;
using std::vector;

void FlipColor(int x, int y, vector<deque<bool>>* image_ptr) {
  vector<deque<bool>>& image = *image_ptr;
  const bool color = image[x][y];

  queue<pair<int, int>> q;
  image[x][y] = !color;  // Flips.
  q.emplace(x, y);
  while (!q.empty()) {
    const auto curr = q.front();
    q.pop();
    for (const auto& next_coor : initializer_list<pair<int, int>>{
             {curr.first, curr.second+1}, {curr.first, curr.second - 1}, 
             {curr.first + 1, curr.second}, {curr.first - 1, curr.second}}) {
      if (next_coor.first >= 0 && next_coor.first < image.size() && next_coor.second >= 0 &&
          next_coor.second < image[next_coor.first].size() && image[next_coor.first][next_coor.second] == color) {
        // Flips the color.
        image[next_coor.first][next_coor.second] = !color;
        q.emplace(next_coor.first, next_coor.second);
      }
    }
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
