#include <vector>
#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include <unordered_map>
using std::vector;


//#define BRUTE_FORCE
#define WITHOUT_TEMP_VECTOR


BinaryTreeNode<int> * BinaryTreeFromPreorderInorderHelper(const vector<int>& preorder, const vector<int>& inorder, int & preorder_index);
BinaryTreeNode<int> * BTFromPreorderInorderHelperWithoutExtraVectors(const vector<int>& preorder, 
                                                                     const vector<int>& inorder, 
                                                                     int & preorder_index, int inorder_start, int inorder_end);
BinaryTreeNode<int> * BTPreorderInorderHelperWithoutExtraVectorsWithHash(const vector<int>& preorder, 
                                                                         const vector<int>& inorder,
                                                                         const std::unordered_map<int, int> & hash_table, 
                                                                         int & preorder_index, int inorder_start, int inorder_end);

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorder(
    const vector<int>& preorder, const vector<int>& inorder) {
  // TODO - you fill in here.
#ifdef BRUTE_FORCE
#pragma message ("BRUTE FORCE")
  int preorder_index = 0;
  return unique_ptr<BinaryTreeNode<int>>(BinaryTreeFromPreorderInorderHelper(preorder, inorder, preorder_index));

#elif defined WITHOUT_TEMP_VECTOR

#pragma message ("WITHOUT TEMP VECTOR")
  int preorder_index = 0;
  int inorder_start = 0;
  int inorder_end = inorder.size();
  return unique_ptr<BinaryTreeNode<int>>(BTFromPreorderInorderHelperWithoutExtraVectors(preorder, inorder, preorder_index, inorder_start, inorder_end));
#else

#pragma message ("WITHOUT TEMP VECTOR AND WITH HASH TABLE")
  std::unordered_map<int, int> hash_table;
  for(int i = 0; i < inorder.size(); i++) {
    hash_table[inorder[i]] = i;
  }

  int preorder_index = 0;
  int inorder_start = 0;
  int inorder_end = inorder.size();
  return unique_ptr<BinaryTreeNode<int>>(BTPreorderInorderHelperWithoutExtraVectorsWithHash(preorder, inorder, hash_table, preorder_index, inorder_start, inorder_end));
#endif
}

#pragma mark THIRD_ATTEMPT
BinaryTreeNode<int> * BTPreorderInorderHelperWithoutExtraVectorsWithHash(const vector<int>& preorder, 
                                                                         const vector<int>& inorder,
                                                                         const std::unordered_map<int, int> & hash_table, 
                                                                         int & preorder_index, int inorder_start, int inorder_end)
{
  if(inorder_start == inorder_end) return nullptr;
  
  BinaryTreeNode<int> * root = new BinaryTreeNode<int>(preorder[preorder_index++]);
  if((inorder_end - inorder_start) == 1) return root;

  int root_index = hash_table.at(root->data);

  BinaryTreeNode<int> * left = BTFromPreorderInorderHelperWithoutExtraVectors(preorder, inorder, preorder_index, inorder_start, root_index);
  root->left.reset(left);

  BinaryTreeNode<int> * right = BTFromPreorderInorderHelperWithoutExtraVectors(preorder, inorder, preorder_index, root_index+1, inorder_end);
  root->right.reset(right);

  return root;
}

#pragma mark SECOND_ATTEMPT
int get_index_of_element_w_start(const vector<int> & v, int start, int elem) {
  int retval = 0;
  for(int i = start; i < v.size(); i++) {
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
  if(inorder_start == inorder_end) return nullptr;
  
  BinaryTreeNode<int> * root = new BinaryTreeNode<int>(preorder[preorder_index++]);
  if((inorder_end - inorder_start) == 1) return root;

  int root_index = get_index_of_element_w_start(inorder, inorder_start, root->data);

  BinaryTreeNode<int> * left = BTFromPreorderInorderHelperWithoutExtraVectors(preorder, inorder, preorder_index, inorder_start, root_index);
  root->left.reset(left);

  BinaryTreeNode<int> * right = BTFromPreorderInorderHelperWithoutExtraVectors(preorder, inorder, preorder_index, root_index+1, inorder_end);
  root->right.reset(right);

  return root;
}

#pragma mark FIRST_ATTEMPT
vector<int> get_subvector(const vector<int> & v, int start, int end) {
  if(start >= end) return {};
  return vector<int>(v.begin()+start, v.begin()+end);
}

int get_index_of_element(const vector<int> & v, int elem) {
  int retval = 0;
  for(int i = 0; i < v.size(); i++) {
    if(elem == v[i]) {
      retval = i;
      break;
    }
  }
  return retval;
}

BinaryTreeNode<int> * BinaryTreeFromPreorderInorderHelper(
  const vector<int>& preorder, const vector<int>& inorder, int & preorder_index) {
  if(inorder.size() == 0) {
    return nullptr;
  }

  BinaryTreeNode<int> * root = new BinaryTreeNode<int>(preorder[preorder_index++]);
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
