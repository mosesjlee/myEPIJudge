#include <memory>
#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
//#define BRUTE_FORCE

BstNode<int>* FindFirstGreaterThanKHelper(const unique_ptr<BstNode<int>>& tree, int k, int upper);

BstNode<int>* FindFirstGreaterThanK(const unique_ptr<BstNode<int>>& tree,
                                    int k) {
  // TODO - you fill in here.
#ifdef BRUTE_FORCE
#pragma message ("BRUTE FORCE")
  if(tree == nullptr) return nullptr;
  return FindFirstGreaterThanKHelper(tree, k, INT_MAX);
#else
#pragma message ("BOOK OPTIMIZED WAY")
  BstNode<int>* subtree = tree.get(), * last_known_node = nullptr;
  while(subtree) {
    if(subtree->data > k) {
      last_known_node = subtree;
      subtree = subtree->left.get();
    }
    else {
      subtree = subtree->right.get();
    }
  }
  return last_known_node;
#endif
}

BstNode<int>* FindFirstGreaterThanKHelper(const unique_ptr<BstNode<int>>& tree, int k, int upper) {
  BstNode<int>* retval = nullptr;
  if(tree == nullptr) return retval;
  if(tree->data > upper) return retval;

  int current_upper = upper;
  if(tree->data < upper && tree->data > k) {
    current_upper = tree->data;
  }

  if(k < tree->data) {
    retval = FindFirstGreaterThanKHelper(tree->left, k, current_upper);
  }
  else {
    retval = FindFirstGreaterThanKHelper(tree->right, k, current_upper);
  }

  if(!retval && (tree->data < upper && tree->data > k)) {
    retval = tree.get();
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
