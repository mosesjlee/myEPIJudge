#include <memory>
#include "bst_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;
//#define BRUTE_FORCE
// Input nodes are nonempty and the key at s is less than or equal to that at
// b.
BstNode<int>* FindLCA(const unique_ptr<BstNode<int>>& tree,
                      const unique_ptr<BstNode<int>>& s,
                      const unique_ptr<BstNode<int>>& b) {
  // TODO - you fill in here.
#ifdef BRUTE_FORCE
  if(tree == nullptr) return nullptr;
  if(s->data < tree->data && b->data < tree->data) {
    return FindLCA(tree->left, s, b);
  }
  if(s->data > tree->data && b->data > tree->data) {
    return FindLCA(tree->right, s, b);
  }

  return tree.get();
#else

  BstNode<int>* iter = tree.get();
  while(iter->data < s->data || iter->data > b->data) {
    while(iter->data < s->data) {
      iter = iter->right.get();
    }

    while(iter->data > b->data) {
      iter = iter->left.get();
    }
  }
  return iter;
#endif  
}

int LcaWrapper(TimedExecutor& executor,
               const std::unique_ptr<BstNode<int>>& tree, int key0, int key1) {
  const unique_ptr<BstNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BstNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return FindLCA(tree, node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_in_bst.cc",
                         "lowest_common_ancestor_in_bst.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
