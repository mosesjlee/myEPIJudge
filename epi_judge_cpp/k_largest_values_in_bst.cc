#include <memory>
#include <vector>
#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;
//#define BRUTE_FORCE
//#define CLEANED_UP

vector<int> FindKLargestInBSTHelper(const unique_ptr<BstNode<int>>& tree, int & k);
void FindKLargestInBSTHelper2(const unique_ptr<BstNode<int>>& tree, int k, vector<int> * retval);
void FindKLargestInBSTHelper3(const unique_ptr<BstNode<int>>& tree, int k, vector<int> * retval);

vector<int> FindKLargestInBST(const unique_ptr<BstNode<int>>& tree, int k) {
  // TODO - you fill in here.
#ifdef BRUTE_FORCE
  int copy_k = k;
  return FindKLargestInBSTHelper(tree, copy_k) ;
#elif defined CLEANED_UP
#pragma message ("CLEANED UP")
  vector<int> retval;
  FindKLargestInBSTHelper2(tree, k, &retval);
  return retval;
#else
#pragma message ("BOOK WAY")
  vector<int> retval;
  FindKLargestInBSTHelper3(tree, k, &retval);
  return retval;
#endif  
}

vector<int> FindKLargestInBSTHelper(const unique_ptr<BstNode<int>>& tree, int & k){
  vector<int> list;
  if(tree == nullptr) return list;
  
  auto right = FindKLargestInBSTHelper(tree->right, k);
  list.insert(list.end(), right.begin(), right.end());

  if(k == 0) return list;
  list.push_back(tree->data);
  k--;

  auto left = FindKLargestInBSTHelper(tree->left, k);
  list.insert(list.end(), left.begin(), left.end());

  return list;
}

void FindKLargestInBSTHelper2(const unique_ptr<BstNode<int>>& tree, int k, vector<int> * retval){
  if(tree == nullptr) return;

  FindKLargestInBSTHelper2(tree->right, k, retval);
  if(retval->size() < k) {
    retval->push_back(tree->data);
  }
  else {
    return;
  }
  FindKLargestInBSTHelper2(tree->left, k, retval);
}

void FindKLargestInBSTHelper3(const unique_ptr<BstNode<int>>& tree, int k, vector<int> * retval) {
  if(tree && (retval->size() < k)) {
    FindKLargestInBSTHelper3(tree->right, k, retval);
    if(retval->size() < k) {
      retval->push_back(tree->data);
      FindKLargestInBSTHelper3(tree->left, k, retval);
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "k_largest_values_in_bst.cc",
                         "k_largest_values_in_bst.tsv", &FindKLargestInBST,
                         &UnorderedComparator<std::vector<int>>, param_names);
}
