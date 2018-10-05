#include "list_node.h"
#include "test_framework/generic_test.h"

void PrintNodes() {

}

shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
                                              shared_ptr<ListNode<int>> L2) {
  // TODO - you fill in here.
  if(L1 == nullptr && L2 == nullptr) return nullptr;
  if(L1 == nullptr) return L2;
  if(L2 == nullptr) return L1;

  shared_ptr<ListNode<int>> anchor_pointer = L1->data <= L2->data ? L1 : L2;
  shared_ptr<ListNode<int>> source_pointer = L1->data <= L2->data ? L2 : L1;
  shared_ptr<ListNode<int>> temp = nullptr;

  while(source_pointer != nullptr) {
    while((anchor_pointer->next != nullptr) && (anchor_pointer->next->data < source_pointer->data)) {
      anchor_pointer = anchor_pointer->next;
    }

    temp = source_pointer->next;
    source_pointer->next = anchor_pointer->next;
    anchor_pointer->next = source_pointer;
    anchor_pointer = anchor_pointer->next;
    source_pointer = temp;
  }

  return L1->data <= L2->data ? L1 : L2;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "sorted_lists_merge.cc",
                         "sorted_lists_merge.tsv", &MergeTwoSortedLists,
                         DefaultComparator{}, param_names);
}
