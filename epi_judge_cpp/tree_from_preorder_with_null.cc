#include <string>
#include <vector>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;
BinaryTreeNode<int> *PreorderReconstructionHelper(const vector<int*>& preorder, int & index);

unique_ptr<BinaryTreeNode<int>> ReconstructPreorder(
    const vector<int*>& preorder) {
  // TODO - you fill in here.
  int index = 0;
  return  unique_ptr<BinaryTreeNode<int>>(PreorderReconstructionHelper(preorder, index));
}

BinaryTreeNode<int> *PreorderReconstructionHelper(const vector<int*>& preorder, int & index) {
  if(preorder[index] == nullptr) {
    return nullptr;
  }

  BinaryTreeNode<int> * root = new BinaryTreeNode<int>(*preorder[index]);
  root->left.reset(PreorderReconstructionHelper(preorder, ++index));
  root->right.reset(PreorderReconstructionHelper(preorder, ++index));
  return root;
}

unique_ptr<BinaryTreeNode<int>> ReconstructPreorderWrapper(
    TimedExecutor& executor, const vector<string>& preorder) {
  vector<int> values;
  vector<int*> ptrs;
  values.reserve(preorder.size());
  for (auto& s : preorder) {
    if (s == "null") {
      ptrs.push_back(nullptr);
    } else {
      int i = std::stoi(s);
      values.push_back(i);
      ptrs.push_back(&values.back());
    }
  }

  return executor.Run([&] { return ReconstructPreorder(ptrs); });
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "preorder"};
  return GenericTestMain(args, "tree_from_preorder_with_null.cc",
                         "tree_from_preorder_with_null.tsv",
                         &ReconstructPreorderWrapper, DefaultComparator{},
                         param_names);
}
