#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
void quick_sort(vector<int> * A_ptr, int begin, int end);
// The numbering starts from one, i.e., if A = [3, 1, -1, 2] then
// FindKthLargest(1, A) returns 3, FindKthLargest(2, A) returns 2,
// FindKthLargest(3, A) returns 1, and FindKthLargest(4, A) returns -1.
int FindKthLargest(int k, vector<int>* A_ptr) {
  // TODO - you fill in here.
  vector<int> & a_copy = *A_ptr;
  int copy_k = k;
  int retval = -1;
  if(k > a_copy.size()) {
    return retval;
  }


  quick_sort(&a_copy, 0, a_copy.size()-1);

  //sort(a_copy.begin(), a_copy.end());
  retval = a_copy[k-1]; //you want to get the kth largest element from the largest
  return retval;
}

int partition(vector<int> * A_ptr, int begin, int end, int part_val) {
  vector<int> & a_copy = *A_ptr;
  int left = begin;
  int right = end;
  while(left <= right) {
    while(a_copy[left] > part_val) {
      left++;
    }

    while(a_copy[right] < part_val) {
      right--;
    }

    if(left <= right) {
      int temp = a_copy[left];
      a_copy[left] = a_copy[right];
      a_copy[right] = temp;
      left++;
      right--;
    }
  }

  return left;
}

void quick_sort(vector<int> * A_ptr, int begin, int end) {
  if(begin >= end) return;
  int part_val = (*A_ptr)[begin + (end-begin)/2];
  int mid = partition(A_ptr, begin, end, part_val);
  quick_sort(A_ptr, begin, mid-1);
  quick_sort(A_ptr, mid, end);
}



int FindKthLargestWrapper(int k, vector<int>& A) {
  return FindKthLargest(k, &A);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k", "A"};
  return GenericTestMain(args, "kth_largest_in_array.cc",
                         "kth_largest_in_array.tsv", &FindKthLargestWrapper,
                         DefaultComparator{}, param_names);
}
