#include <vector>
#include "binary_tree_with_parent_prototype.h"
#include "test_framework/generic_test.h"
using std::vector;

#define BRUTE_FORCE

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  // TODO - you fill in here.
  vector<int> retval;
  BinaryTreeNode<int> * iter = tree.get();
  BinaryTreeNode<int> * prev = nullptr;

#ifdef BRUTE_FORCE
#pragma message("Brute Force")
  //Start at the left most node
  while(iter && iter->left) {
    iter = iter->left.get();
  }

  while(iter != nullptr) {
    if(prev == nullptr || prev == iter->left.get()) {
      retval.push_back(iter->data);
    }
    else if(prev == iter->right.get()) {
      prev = iter;
      iter = iter->parent;
      continue;
    }

    if(iter->right) {
      prev = nullptr;
      iter = iter->right.get();
      while(iter->left) {
        iter = iter->left.get();
      }
    }
    else {
      prev = iter;
      iter = iter->parent;
    }
  }
#else //Optimized
#pragma message("Optimized")

  //This is the book's optmized version
  //I expanded the ternary and the temporary variable 'next' to better understand

  while(iter != nullptr) {
    if(prev == iter->parent) {
      if(iter->left != nullptr) {
        prev = iter;
        iter = iter->left.get();
      }
      else {
        retval.push_back(iter->data);
        if(iter->right != nullptr) {
          prev = iter;
          iter = iter->right.get();
        }
        else {
          prev = iter;
          iter = iter->parent;
        }
      }
    }
    else if(prev == iter->left.get()) {
      retval.push_back(iter->data);
      if(iter->right != nullptr) {
        prev = iter;
        iter = iter->right.get();
      }
      else {
        prev = iter;
        iter = iter->parent;
      }
    }
    else {
      prev = iter;
      iter = iter->parent;
    }
  }

#endif
  return retval;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_with_parent_inorder.cc",
                         "tree_with_parent_inorder.tsv", &InorderTraversal,
                         DefaultComparator{}, param_names);
}
