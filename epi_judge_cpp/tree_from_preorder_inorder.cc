#include <vector>
#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
using std::vector;

#define BRUTE_FORCE

BinaryTreeNode<int> * BinaryTreeFromPreorderInorderHelper(const vector<int>& preorder, const vector<int>& inorder, int & preorder_index);
BinaryTreeNode<int> * BTFromPreorderInorderHelperWithoutExtraVectors(const vector<int>& preorder, const vector<int>& inorder, int & preorder_index);

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorder(
    const vector<int>& preorder, const vector<int>& inorder) {
  // TODO - you fill in here.
#ifdef BRUTE_FORCE
  int preorder_index = 0;
  return unique_ptr<BinaryTreeNode<int>>(BinaryTreeFromPreorderInorderHelper(preorder, inorder, preorder_index));
#else
  int preorder_index = 0;
  return unique_ptr<BinaryTreeNode<int>>(BinaryTreeFromPreorderInorderHelper2(preorder, inorder, preorder_index));
 #endif
}

void print_vector(const vector<int>& v) {
  for(int i : v) {
    std::cout << i << " ,";
  }
  std::cout << std::endl;
}



int get_index_of_element(const vector<int> & v, int elem) {
  int retval = -1;
  for(int i = 0; i < v.size(); i++) {
    if(elem == v[i]) {
      retval = i;
      break;
    }
  }
  return retval;
}

BinaryTreeNode<int> * BTFromPreorderInorderHelperWithoutExtraVectors(const vector<int>& preorder, 
                                                                     const vector<int>& inorder, 
                                                                     int & preorder_index, int inorder_start, int inorder_end)
{
  
  BinaryTreeNode<int> * root = new BinaryTreeNode<int>(preorder[0]);
  int root_val = root->data;
  int root_index = get_index_of_element(inorder, root_val);

  auto left = BTFromPreorderInorderHelperWithoutExtraVectors(preorder);
  root->left.reset(left);

  auto right = BTFromPreorderInorderHelperWithoutExtraVectors(preorder);
  root->right.reset(right);

  return root;
}

vector<int> get_subvector(const vector<int> & v, int start, int end) {
  if(start >= end) return {};
  return vector<int>(v.begin()+start, v.begin()+end);
}

BinaryTreeNode<int> * BinaryTreeFromPreorderInorderHelper(
  const vector<int>& preorder, const vector<int>& inorder, int & preorder_index) {
  if(inorder.size() == 0) {
    return nullptr;
  }

  BinaryTreeNode<int> * root = new BinaryTreeNode<int>(preorder[preorder_index]);
  preorder_index++;
  if(inorder.size() == 1) {
    return root;
  }

  int root_val = root->data;
  int root_index = get_index_of_element(inorder, root_val);
  vector<int> first_half = get_subvector(inorder, 0, root_index);
  vector<int> second_half = get_subvector(inorder, root_index+1, inorder.size());

  BinaryTreeNode<int> * left = BinaryTreeFromPreorderInorderHelper(preorder, first_half, preorder_index);
  root->left.reset(left);

  BinaryTreeNode<int> * right  = BinaryTreeFromPreorderInorderHelper(preorder, second_half, preorder_index);
  root->right.reset(right);

  return root;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder", "inorder"};
  return GenericTestMain(
      args, "tree_from_preorder_inorder.cc", "tree_from_preorder_inorder.tsv",
      &BinaryTreeFromPreorderInorder, DefaultComparator{}, param_names);
}
