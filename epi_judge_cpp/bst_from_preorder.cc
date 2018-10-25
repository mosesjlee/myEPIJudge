#include <memory>
#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

#define BRUTE_FORCE

BstNode<int> * RebuildBSTFromPreorderHelper(const vector<int>& preorder_sequence, int low, int high);
BstNode<int> * RebuildBSTFromPreorderHelper2(const vector<int>* preorder_sequence, int low, int high, int & root_idx);

unique_ptr<BstNode<int>> RebuildBSTFromPreorder(
    const vector<int>& preorder_sequence) {
  // TODO - you fill in here.
#ifdef BRUTE_FORCE
#pragma message ("BRUTE_FORCE")
  return unique_ptr<BstNode<int>>(RebuildBSTFromPreorderHelper(preorder_sequence, 0, preorder_sequence.size()));
#else
#pragma message ("OPTIMIZED")
  int root_idx = 0;
  return unique_ptr<BstNode<int>>(RebuildBSTFromPreorderHelper2(&preorder_sequence, INT_MIN, INT_MAX, root_idx));
#endif
}

BstNode<int> * RebuildBSTFromPreorderHelper(const vector<int>& preorder_sequence, int low, int high) {
  if(high-low < 1) return nullptr;

  BstNode<int> * root = new BstNode<int>(preorder_sequence[low]);
  int right_index = high;

  for(int i = low; i < high; i++) {
    if(root->data < preorder_sequence[i]) {
      right_index = i;
      break;
    }
  }
  root->left.reset(RebuildBSTFromPreorderHelper(preorder_sequence, low+1, right_index));
  root->right.reset(RebuildBSTFromPreorderHelper(preorder_sequence, right_index, high));
  return root;
}

BstNode<int> * RebuildBSTFromPreorderHelper2(const vector<int>* preorder_sequence, int low, int high, int & root_idx) {
  if(root_idx == preorder_sequence->size()) {
    return nullptr;
  }

  int root_val = preorder_sequence->at(root_idx);
  if(root_val > high || root_val < low) {
    return nullptr;
  }
  root_idx++;
  auto left = RebuildBSTFromPreorderHelper2(preorder_sequence, low, root_val, root_idx);
  auto right = RebuildBSTFromPreorderHelper2(preorder_sequence, root_val, high, root_idx);
  BstNode<int> * root = new BstNode<int>(root_val);
  root->left.reset(left);
  root->right.reset(right);
  return root;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder_sequence"};
  return GenericTestMain(args, "bst_from_preorder.cc", "bst_from_preorder.tsv",
                         &RebuildBSTFromPreorder, DefaultComparator{},
                         param_names);
}
