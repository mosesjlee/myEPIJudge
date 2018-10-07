#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> EvenOddMerge(const shared_ptr<ListNode<int>>& L) {
  // TODO - you fill in here.
  shared_ptr<ListNode<int>> even_dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, L});
  shared_ptr<ListNode<int>> odd_dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, nullptr});
  auto even_list_head = even_dummy_head;
  auto even_iter = even_dummy_head->next;
  auto odd_list_head = odd_dummy_head;

  while(even_iter) {
    if(even_iter->data & 1) {
      even_list_head->next = even_iter->next;
      odd_list_head->next = even_iter;
      even_iter->next = nullptr;
      odd_list_head = odd_list_head->next;
      even_iter = even_list_head->next;
    }
    else {
      even_list_head = even_list_head->next;
      even_iter = even_iter->next;
    }
  }

  even_list_head->next = odd_dummy_head->next;
  return even_dummy_head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "even_odd_list_merge.cc",
                         "even_odd_list_merge.tsv", &EvenOddMerge,
                         DefaultComparator{}, param_names);
}
