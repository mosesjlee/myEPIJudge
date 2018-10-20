#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;
#define BRUTE_FORCE
struct Event {
  int start, finish;
};
int FindMaxSimultaneousEvents(const vector<Event>& A) {
  // TODO - you fill in here.
  int layers = 0;
#ifdef BRUTE_FORCE
  vector<Event> A_copy(A);
  //1st sort
  std::sort(A_copy.begin(), A_copy.end(), [](const Event & a, const Event & b){ return a.start < b.start; });
  
  while(!A_copy.empty()) {
    int prev_finish = -1;
    auto it = A_copy.begin();
    while(it != A_copy.end()) {
      if(prev_finish < it->start) {
        prev_finish = it->finish;
        it = A_copy.erase(it);
      }
      else {
        it++;
      }
    }
    layers++;
  }
#else
#endif
  return layers;
}
template <>
struct SerializationTraits<Event> : UserSerTraits<Event, int, int> {};

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "calendar_rendering.cc",
                         "calendar_rendering.tsv", &FindMaxSimultaneousEvents,
                         DefaultComparator{}, param_names);
}
