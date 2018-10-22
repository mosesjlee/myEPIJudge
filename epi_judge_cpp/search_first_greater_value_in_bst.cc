#include <memory>
#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

BstNode<int>* FindFirstGreaterThanK(const unique_ptr<BstNode<int>>& tree,
                                    int k) {
  // TODO - you fill in here.
  BstNode<int>* retval = nullptr;
  if(tree == nullptr) return retval;

  return retval;
}

BstNode<int>* FindK(const unique_ptr<BstNode<int>>& tree, int k) {
  BstNode<int>* retval = nullptr;
  if(tree == nullptr) return retval;

  if(k == tree->data) {
    retval = tree.get();
  }
  else if(k < tree->data) {
    retval = FindK(tree->left, k);
  }
  else {
    retval = FindK(tree->right, k);
  }

  return retval;
}


int FindFirstGreaterThanKWrapper(const unique_ptr<BstNode<int>>& tree, int k) {
  auto result = FindFirstGreaterThanK(tree, k);
  return result ? result->data : -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "search_first_greater_value_in_bst.cc",
                         "search_first_greater_value_in_bst.tsv",
                         &FindFirstGreaterThanKWrapper, DefaultComparator{},
                         param_names);
}
