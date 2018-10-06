#include <memory>
#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

// Assumes L has at least k nodes, deletes the k-th last node in L.
shared_ptr<ListNode<int>> RemoveKthLast(const shared_ptr<ListNode<int>>& L,
                                        int k) {
  // TODO - you fill in here.
  shared_ptr<ListNode<int>> dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, L}); 
  shared_ptr<ListNode<int>> look_ahead = L, stay_behind = dummy_head;

  while( k-- > 0) {
    look_ahead = look_ahead->next;
  }

  while(look_ahead) {
    look_ahead = look_ahead->next;
    stay_behind = stay_behind->next;
  }
  stay_behind->next = stay_behind->next ? stay_behind->next->next : nullptr;

  return dummy_head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "k"};
  return GenericTestMain(args, "delete_kth_last_from_list.cc",
                         "delete_kth_last_from_list.tsv", &RemoveKthLast,
                         DefaultComparator{}, param_names);
}
