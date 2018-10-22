#include <memory>
#include <queue>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#define main _main
#include "tree_inorder.cc"
#undef main
using std::unique_ptr;
//#define CLEANED_UP
#define FIRST_ATTEMPT
bool IsBinaryTreeBSTHelper(const unique_ptr<BinaryTreeNode<int>>& tree, int lower, int upper);

struct QueueEntry {
  BinaryTreeNode<int> * Node;
  int lower, upper;
};

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
  // TODO - you fill in here.
#ifdef FIRST_ATTEMPT
#pragma message ("FIRST ATTEMPT")
  bool retval = true;
  if(tree == nullptr) return retval;
  vector<int> tree_data = InorderTraversal(tree);

  for(int i = 0; i < tree_data.size()-1; i++) {
    if(tree_data[i] > tree_data[i+1]) {
      retval = false;
      break;
    }
  }

  return retval;
#elif defined CLEANED_UP
#pragma message ("MY CLEANED UP ATTEMPT")

  return IsBinaryTreeBSTHelper(tree, INT_MIN, INT_MAX);
#else
#pragma message ("MOST TIME EFFICIENT FROM BOOK")
  if(tree == nullptr) return true;
  std::queue<QueueEntry> bfs_queue;
  bfs_queue.emplace(QueueEntry{tree.get(), INT_MIN, INT_MAX});

  while(!bfs_queue.empty()) {
    QueueEntry next_entry = bfs_queue.front();
    if(next_entry.Node->data < next_entry.lower || 
        next_entry.Node->data > next_entry.upper) 
      return false;

    if(next_entry.Node->left)
      bfs_queue.emplace(QueueEntry{next_entry.Node->left.get(), next_entry.lower, next_entry.Node->data});
    if(next_entry.Node->right)
      bfs_queue.emplace(QueueEntry{next_entry.Node->right.get(), next_entry.Node->data, next_entry.upper});

    bfs_queue.pop();
  }

  return true;
#endif
}

bool IsBinaryTreeBSTHelper(const unique_ptr<BinaryTreeNode<int>>& tree, int lower, int upper)
{
  if(tree == nullptr) return true;
  if(tree->data < lower || tree->data > upper) return false;
  return IsBinaryTreeBSTHelper(tree->left, lower, tree->data) 
      && IsBinaryTreeBSTHelper(tree->right, tree->data, upper);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                         &IsBinaryTreeBST, DefaultComparator{}, param_names);
}
