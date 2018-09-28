#include <tuple>
#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
struct Rect {
  int x, y, width, height;
};

bool operator==(const Rect& r1, const Rect& r2) {
  return std::tie(r1.x, r1.y, r1.width, r1.height) ==
         std::tie(r2.x, r2.y, r2.width, r2.height);
}

Rect IntersectRectangle(const Rect& R1, const Rect& R2) {
  // TODO - you fill in here.
  if(R1 == R2) return R1;

  Rect retval = {0, 0, -1, -1};

  //My idea is take the difference of the starting point
  //If the difference is greater than the width the side is not
  //intersecting
  if(R1.x - R2.x > R2.width || R2.x - R1.x > R1.width) {
    return retval;
  }
  if(R1.y - R2.y > R2.height || R2.y - R1.y > R1.height) {
    return retval;
  }

  //Find the lowest point out and subtract the greatest location point
  retval.width = fmin(R1.x + R1.width, R2.x + R2.width) - fmax(R1.x, R2.x);
  retval.height = fmin(R1.y + R1.height, R2.y+ R2.height) - fmax(R1.y, R2.y);

  retval.x = fmax(R1.x, R2.x);
  retval.y = fmax(R1.y, R2.y);
  return retval;
}


template <>
struct SerializationTraits<Rect> : UserSerTraits<Rect, int, int, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
    return {FmtStr("area({})", arg_name), FmtStr("perimeter({})", arg_name),
            FmtStr("max(w, h)({})", arg_name)};
  }

  static std::vector<int> GetMetrics(const Rect& x) {
    return {x.height * x.width, 2 * (x.height + x.width),
            std::max(x.height, x.width)};
  }
};

std::ostream& operator<<(std::ostream& out, const Rect& r) {
  return PrintTo(out, std::make_tuple(r.x, r.y, r.width, r.height));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"R1", "R2"};
  return GenericTestMain(args, "rectangle_intersection.cc",
                         "rectangle_intersection.tsv", &IntersectRectangle,
                         DefaultComparator{}, param_names);
}
