#include <memory>
#include <vector>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  // TODO - you fill in here.
  vector<int> list;
  if(tree == nullptr) return list;
  auto left = InorderTraversal(tree->left);
  list.insert(list.end(), left.begin(), left.end());

  list.push_back(tree->data);

  auto right = InorderTraversal(tree->right);
  list.insert(list.end(), right.begin(), right.end());

  return list;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_inorder.cc", "tree_inorder.tsv",
                         &InorderTraversal, DefaultComparator{}, param_names);
}
