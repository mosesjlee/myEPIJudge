#include <algorithm>
#include <cmath>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_utils.h"
using std::vector;

struct Star {
  bool operator<(const Star& that) const {
    return Distance() < that.Distance();
  }

  double Distance() const { return sqrt(x * x + y * y + z * z); }

  double x, y, z;
};

vector<Star> FindClosestKStars(vector<Star>::const_iterator stars_begin,
                               const vector<Star>::const_iterator& stars_end,
                               int k) {
  // TODO - you fill in here.
  vector<Star> retval;

#ifdef EXPLICIT_DEF
  std::priority_queue<Star, vector<Star>, std::function<bool(Star, Star)>>
  max_heap([](const Star & a, const Star & b){
    return a.Distance() < b.Distance();
  });
#else
  std::priority_queue<Star> max_heap;
#endif

  for(int i = 0; i < k; i++) {
    max_heap.push(*stars_begin++);
  }

  while(stars_begin != stars_end) {
    if(stars_begin->Distance() < max_heap.top().Distance()){
      max_heap.pop();
      max_heap.push(*stars_begin);
    }
    stars_begin++;
  }

  while(!max_heap.empty()) {
    retval.emplace_back(max_heap.top());
    max_heap.pop();
  }
  return retval;
}

template <>
struct SerializationTraits<Star> : UserSerTraits<Star, double, double, double> {
};

std::ostream& operator<<(std::ostream& out, const Star& s) {
  return out << s.Distance();
}

bool Comp(const vector<double>& expected, vector<Star> output) {
  if (output.size() != expected.size()) {
    return false;
  }

  std::sort(begin(output), end(output));

  for (int i = 0; i < output.size(); ++i) {
    if (!DefaultComparator()(output[i].Distance(), expected[i])) {
      return false;
    }
  }
  return true;
}

vector<Star> FindClosestKStarsWrapper(const vector<Star>& stars, int k) {
  return FindClosestKStars(cbegin(stars), cend(stars), k);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"stars", "k"};
  return GenericTestMain(args, "k_closest_stars.cc", "k_closest_stars.tsv",
                         &FindClosestKStarsWrapper, &Comp, param_names);
}
