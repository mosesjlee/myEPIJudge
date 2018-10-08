#include <memory>
#include <vector>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include <array>

using std::unique_ptr;
using std::vector;

vector<vector<int>> BinaryTreeDepthOrder(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  // TODO - you fill in here.
  vector<vector<int>> retval;
  if(!tree.get()) return retval;
  BinaryTreeNode<int> * root = tree.get();

  //The queue to use
  std::array<std::queue<BinaryTreeNode<int>* >, 2> pair_of_queues;

  //Add the root to the queue
  pair_of_queues[0].push(root);

  int turn = 0; 
  while(!pair_of_queues[0].empty() || !pair_of_queues[1].empty()) {
    vector<int> data_level;
    //visit node
    while(!pair_of_queues[turn].empty()) {
      BinaryTreeNode<int> * curr_node = pair_of_queues[turn].front();
      pair_of_queues[turn].pop();
      data_level.push_back(curr_node->data);
      //queue children
      if(curr_node->left.get()) pair_of_queues[turn ^ 1].push(curr_node->left.get());
      if(curr_node->right.get()) pair_of_queues[turn ^ 1].push(curr_node->right.get());
    }
  
    //add data to the retval
    retval.push_back(data_level);
    data_level.clear();
    turn ^= 1;
  }

  return retval;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                         &BinaryTreeDepthOrder, DefaultComparator{},
                         param_names);
}
