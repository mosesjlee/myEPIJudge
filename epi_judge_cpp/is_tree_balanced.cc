#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include <stack>
int tree_height(BinaryTreeNode<int> * root);
bool is_tree_balanced(BinaryTreeNode<int> * root, int & height);

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  // TODO - you fill in here.
  BinaryTreeNode<int> * root = tree.get();
  int height = 0;
  return is_tree_balanced(root, height);
}

bool is_tree_balanced(BinaryTreeNode<int> * root, int & height) {
  if(root == nullptr) {
    height = -1;
    return true;
  }

  int left_height = 0, right_height = 0;
  bool left_balanced = is_tree_balanced(root->left.get(), left_height);
  left_height += 1;
  bool right_balanced = is_tree_balanced(root->right.get(), right_height);
  right_height += 1;

  height = fmax(left_height, right_height);
  int heigh_diff = abs(left_height-right_height);

  return left_balanced && right_balanced && (heigh_diff <= 1);
}

int tree_height(BinaryTreeNode<int> * root) {
  if(root == nullptr) return -1;

  int left_height = tree_height(root->left.get());
  int right_height = tree_height(root->right.get());

  return left_height > right_height ? left_height + 1 : right_height + 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
