#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
bool IsSymmetricHelper(BinaryTreeNode<int> * root_1, BinaryTreeNode<int> * root_2);
bool IsTreeEqual(BinaryTreeNode<int> * root_1, BinaryTreeNode<int> * root_2);
void FlipTree(BinaryTreeNode<int> * root);
// #define BRUTE_FORCE
bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>>& tree) {
  // TODO - you fill in here.
  if(tree == nullptr) {
    return true;
  }

  BinaryTreeNode<int> * left = tree->left.get();
  BinaryTreeNode<int> * right = tree->right.get();
#ifdef BRUTE_FORCE
#pragma message ("BRUTE_FORCE")
  FlipTree(left);

  return IsTreeEqual(left, right);
#else
#pragma message ("OPTIMIZED")
  return IsSymmetricHelper(left, right);
#endif
}

bool IsSymmetricHelper(BinaryTreeNode<int> * root_1, BinaryTreeNode<int> * root_2){
  if(root_1 == nullptr && root_2 == nullptr) {
    return true;
  }

  //Since the first if checks for 2 of them being nullptr
  //We can just check if one of them is nullptr
  if(root_1 == nullptr || root_2 == nullptr) {
    return false;
  }

  bool left_equal = IsSymmetricHelper(root_1->left.get(), root_2->right.get());
  bool right_equal = IsSymmetricHelper(root_1->right.get(), root_2->left.get());

  return left_equal && right_equal && (root_1->data == root_2->data);
}

bool IsTreeEqual(BinaryTreeNode<int> * root_1, BinaryTreeNode<int> * root_2) {
  if(root_1 == nullptr && root_2 == nullptr) {
    return true;
  }
  if((root_1 == nullptr && root_2 != nullptr) || (root_1 != nullptr && root_2 == nullptr)) {
    return false;
  }

  bool left_equal = IsTreeEqual(root_1->left.get(), root_2->left.get());
  bool right_equal = IsTreeEqual(root_1->right.get(), root_2->right.get());

  return left_equal && right_equal && (root_1->data == root_2->data);
}

void FlipTree(BinaryTreeNode<int> * root) {
  if(root == nullptr) return;

  FlipTree(root->left.get());
  FlipTree(root->right.get());

  root->left.swap(root->right);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_symmetric.cc", "is_tree_symmetric.tsv",
                         &IsSymmetric, DefaultComparator{}, param_names);
}
