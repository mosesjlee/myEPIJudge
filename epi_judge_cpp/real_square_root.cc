#include "test_framework/generic_test.h"

//From the book
typedef enum {kLarger, kEqual, kSmaller} Ordering;
Ordering Compare(const double a, const double b);
#define BRUTE_FORCE
double SquareRoot(double x) {
  // TODO - you fill in here.
  double lower = 1.0, upper = x;
#ifdef BRUTE_FORCE
#pragma message("BRUTE FORCE")
  //My brute force works for all values except 0.0.
  //I know why because the epsilon is so small.
  //Need to come up with a way work with 0.0

  if(x <= 1.0) { //IF LESS THEN OR EQUAL TO 1 JUST FLIP THE LOWER AND UPPER
    //THE REASON WHY 0 DIDNT WORK WAS BECAUSE OF MY APPROACH
    //KEEP THE APPROACH SIMPLE
    // do {
    //   upper *= 2.0;
    // } while(upper * upper <= x);

    upper = 1.0;
    lower = x;
  }

  while(fabs(upper - lower) > 0.00000001) {
    double mid = lower + (upper - lower)/2.0;
    double mid_squared = mid * mid;
    if(mid_squared > x) {
      upper = mid;
    }
    else {
      lower = mid;
    }
  }
#else
  if(x <= 1.0) {
    lower = x;
    upper = 1.0;
  }

  while(Compare(upper, lower) != kEqual) {
    double mid = lower + 0.5 * (upper - lower);
    double mid_squared = mid * mid;
    if(mid_squared && Compare(mid_squared, x) == kLarger) {
      upper = mid;
    }
    else {
      lower = mid;
    }
  }
#endif
  return lower;
}

//FROM THE BOOK
Ordering Compare(const double a, const double b) {
  double diff = (a-b)/std::max(abs(a), abs(b));
  if(diff < -std::numeric_limits<double>::epsilon()) return kSmaller;
  if(diff > std::numeric_limits<double>::epsilon()) return kLarger;
  return kEqual;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "real_square_root.cc", "real_square_root.tsv",
                         &SquareRoot, DefaultComparator{}, param_names);
}
