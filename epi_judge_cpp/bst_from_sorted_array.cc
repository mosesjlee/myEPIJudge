#include <memory>
#include <vector>
#include "bst_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;
using std::vector;

BstNode<int> * SortedArrayTreeHelper(const vector<int> & A, int start, int end);

unique_ptr<BstNode<int>> BuildMinHeightBSTFromSortedArray(
    const vector<int>& A) {
  // TODO - you fill in here.
  return unique_ptr<BstNode<int>>(SortedArrayTreeHelper(A, 0, A.size()));
}

BstNode<int> * SortedArrayTreeHelper(const vector<int> & A, int start, int end) {
  if((end - start) == 0)
    return nullptr;

  int root_idx = (start + (end-start)/2);
  BstNode<int> * root = new BstNode<int>(A[root_idx]);
  root->left.reset(SortedArrayTreeHelper(A, start, root_idx));
  root->right.reset(SortedArrayTreeHelper(A, root_idx+1, end));
  return root;
}


int BuildMinHeightBSTFromSortedArrayWrapper(TimedExecutor& executor,
                                            const vector<int>& A) {
  unique_ptr<BstNode<int>> result =
      executor.Run([&] { return BuildMinHeightBSTFromSortedArray(A); });

  if (GenerateInorder(result) != A) {
    throw TestFailure("Result binary tree mismatches input array");
  }
  return BinaryTreeHeight(result);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A"};
  return GenericTestMain(args, "bst_from_sorted_array.cc",
                         "bst_from_sorted_array.tsv",
                         &BuildMinHeightBSTFromSortedArrayWrapper,
                         DefaultComparator{}, param_names);
}
