#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/timed_executor.h"
using std::vector;
//#define ITERATION_1
struct Interval {
  struct Endpoint {
    bool is_closed;
    int val;
  };

  Endpoint left, right;
};

vector<Interval> UnionOfIntervals(vector<Interval> intervals) {
  // TODO - you fill in here.
  vector<Interval> retval;

  std::sort(intervals.begin(), intervals.end(),[](const Interval & a, const Interval & b){
    return a.left.val != b.left.val ? a.left.val < b.left.val : (a.left.is_closed && !b.left.is_closed);
  });

  int start_val = -1; int furthest_end_point = -1; 
  bool start_closed = false; bool end_closed = false; 

  for(Interval i : intervals) { 
    if(i.left.val > furthest_end_point || (i.left.val == furthest_end_point && (!i.left.is_closed && !end_closed))) {
      retval.emplace_back(Interval({{start_closed, start_val}, {end_closed, furthest_end_point}}));
      start_val = i.left.val;
      start_closed = i.left.is_closed;
      furthest_end_point = i.right.val;
      end_closed = i.right.is_closed;
    } 
    else { //i.left.val < furthest_end
      if(furthest_end_point < i.right.val) {
        furthest_end_point = i.right.val;
        end_closed = i.right.is_closed;
      }
      else if(furthest_end_point == i.right.val) {
        end_closed = i.right.is_closed | end_closed;
      }
    }
  }

  //For the final element
  retval.emplace_back(Interval({{start_closed, start_val}, {end_closed, furthest_end_point}}));

  //Skip the first element
  return {retval.begin()+1, retval.end()};
}
struct FlatInterval {
  int left_val;
  bool left_is_closed;
  int right_val;
  bool right_is_closed;

  FlatInterval(int left_val, bool left_is_closed, int right_val,
               bool right_is_closed)
      : left_val(left_val),
        left_is_closed(left_is_closed),
        right_val(right_val),
        right_is_closed(right_is_closed) {}

  explicit FlatInterval(Interval in)
      : left_val(in.left.val),
        left_is_closed(in.left.is_closed),
        right_val(in.right.val),
        right_is_closed(in.right.is_closed) {}

  operator Interval() const {
    return {{left_is_closed, left_val}, {right_is_closed, right_val}};
  }

  bool operator==(const FlatInterval& rhs) const {
    return std::tie(left_val, left_is_closed, right_val, right_is_closed) ==
           std::tie(rhs.left_val, rhs.left_is_closed, rhs.right_val,
                    rhs.right_is_closed);
  }
};

template <>
struct SerializationTraits<FlatInterval>
    : UserSerTraits<FlatInterval, int, bool, int, bool> {};

std::ostream& operator<<(std::ostream& out, const FlatInterval& i) {
  return out << (i.left_is_closed ? '<' : '(') << i.left_val << ", "
             << i.right_val << (i.right_is_closed ? '>' : ')');
}

std::vector<FlatInterval> UnionOfIntervalsWrapper(
    TimedExecutor& executor, const std::vector<FlatInterval>& intervals) {
  std::vector<Interval> casted;
  for (const FlatInterval& i : intervals) {
    casted.push_back(static_cast<Interval>(i));
  }

  std::vector<Interval> result =
      executor.Run([&] { return UnionOfIntervals(casted); });

  return {begin(result), end(result)};
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "intervals"};
  return GenericTestMain(args, "intervals_union.cc", "intervals_union.tsv",
                         &UnionOfIntervalsWrapper, DefaultComparator{},
                         param_names);
}
