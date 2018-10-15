#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
//#define FIRST_ATTEMPT
int SearchFirstOfK(const vector<int>& A, int k) {
  // TODO - you fill in here.
#ifdef FIRST_ATTEMPT
  if(binary_search(A.begin(), A.end(), k)) {
    auto it = lower_bound(A.begin(), A.end(), k);
    return it - A.begin();
  }
  return -1;
#else
  long index = -1;
  long low = 0, high = A.size()-1;
  while(low <= high) {
    long mid = low + ((high - low)/2);
    
    if(mid != 0 && k < A[mid]) {
      high = mid-1; //mid - 1 becuase you already checked mid
    }
    else if(k == A[mid]) {
      index = mid;
      high = mid-1; //mid - 1 becuase you already checked mid
    }
    else {
      low = mid+1; //mid + 1 because you already checked mid
    }
  }
  return index;
#endif
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
                         &SearchFirstOfK, DefaultComparator{}, param_names);
}
