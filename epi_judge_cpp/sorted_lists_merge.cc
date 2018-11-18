#include "list_node.h"
#include "test_framework/generic_test.h"
#define FIRST_ATTEMPT
shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
                                              shared_ptr<ListNode<int>> L2) {
  // TODO - you fill in here.
#ifdef FIRST_ATTEMPT
  if(L1 == nullptr && L2 == nullptr) return nullptr;
  if(L1 == nullptr) return L2;
  if(L2 == nullptr) return L1;

  shared_ptr<ListNode<int>> anchor_pointer = L1->data <= L2->data ? L1 : L2;
  shared_ptr<ListNode<int>> source_pointer = L1->data <= L2->data ? L2 : L1;
  shared_ptr<ListNode<int>> temp = nullptr;

  while(source_pointer) {
    //Relying on short circuting when to break anchor_pointer->next is null
    while(anchor_pointer->next && (anchor_pointer->next->data < source_pointer->data)) {
      anchor_pointer = anchor_pointer->next;
    }

    temp = source_pointer->next;
    source_pointer->next = anchor_pointer->next;
    anchor_pointer->next = source_pointer;
    anchor_pointer = anchor_pointer->next;
    source_pointer = temp;
  }

  return L1->data <= L2->data ? L1 : L2;
#else
#pragma message ("SECOND ATTEMPT")
  shared_ptr<ListNode<int>> dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, nullptr});
  shared_ptr<ListNode<int>> final_list_iter = dummy_head;

  while(L1 && L2) {
    if(L1->data <= L2->data) {
      final_list_iter->next = L1;
      L1 = L1->next;
    }
    else {
      final_list_iter->next = L2;
      L2 = L2->next;
    }
    final_list_iter = final_list_iter->next;
  }

  if(L1 != nullptr) final_list_iter->next = L1;
  else final_list_iter->next = L2;

  return dummy_head->next;
#endif  
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "sorted_lists_merge.cc",
                         "sorted_lists_merge.tsv", &MergeTwoSortedLists,
                         DefaultComparator{}, param_names);
}
