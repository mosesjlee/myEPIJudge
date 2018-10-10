#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

int NodeDepth(BinaryTreeNode<int> * node);
void AdvanceNode(BinaryTreeNode<int> ** node, int levels);
BinaryTreeNode<int> * Traverse(BinaryTreeNode<int> * node0, BinaryTreeNode<int> * node1);

BinaryTreeNode<int>* LCA(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  // TODO - you fill in here.
  BinaryTreeNode<int> * node0_copy = node0.get();
  BinaryTreeNode<int> * node1_copy = node1.get();

  int node0_depth = NodeDepth(node0_copy);
  int node1_depth = NodeDepth(node1_copy);

  AdvanceNode(node0_depth > node1_depth ? &node0_copy : &node1_copy, abs(node0_depth-node1_depth));

  return Traverse(node0_copy, node1_copy);
}

int NodeDepth(BinaryTreeNode<int> * node) {
  if(node == nullptr)
    return -1;

  return 1 + NodeDepth(node->parent);
}

void AdvanceNode(BinaryTreeNode<int> ** node, int levels) {
  for(int i = 0; i < levels; i++) {
    (*node) = (*node)->parent;
  }
}

BinaryTreeNode<int> * Traverse(BinaryTreeNode<int> * node0, BinaryTreeNode<int> * node1) {
  if(node0 == node1) 
    return node0;

  return Traverse(node0->parent, node1->parent);
}

int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return LCA(node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
