#include <memory>
#include <unordered_set>
#include <array>
#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

using std::unique_ptr;
#define BRUTE_FORCE
BinaryTreeNode<int>* LCA(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  // TODO - you fill in here.
#ifdef BRUTE_FORCE
#pragma message("BRUTE_FORCE")
  std::unordered_set<int> node_0_ancestors;
  BinaryTreeNode<int> * node_iter = node0.get();
  while(node_iter != nullptr) {
    node_0_ancestors.insert(node_iter->data);
    node_iter = node_iter->parent;
  }

  node_iter = node1.get();
  while(node_iter != nullptr) {
    if(node_0_ancestors.count(node_iter->data)) {
      break;
    }
    node_iter = node_iter->parent;
  }

  return node_iter;
#else
#pragma message("OPTIMIZED ATTEMPT")
  std::unordered_set<int> ancestors;
  BinaryTreeNode<int> *node0_iter = node0.get();
  BinaryTreeNode<int> *node1_iter = node1.get();
  
  while(node0_iter != nullptr || node1_iter != nullptr) {
    if(node0_iter) {
      if(ancestors.count(node0_iter->data)) {
        return node0_iter;
      }
      else {
        ancestors.insert(node0_iter->data);
        node0_iter = node0_iter->parent;
      }
    }
    if(node1_iter) {
      if(ancestors.count(node1_iter->data)) {
        return node1_iter; 
      }
      else {
        ancestors.insert(node1_iter->data);
        node1_iter = node1_iter->parent;
      }
    }
  }

  return nullptr;
#endif
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
  return GenericTestMain(args, "lowest_common_ancestor_close_ancestor.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
