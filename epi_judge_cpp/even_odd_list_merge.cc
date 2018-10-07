#include "list_node.h"
#include "test_framework/generic_test.h"
#include <array>
using std::array;
shared_ptr<ListNode<int>> EvenOddMerge(const shared_ptr<ListNode<int>>& L) {
  // TODO - you fill in here.
#ifdef MY_ORIG_INTERPRETATION
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
#elif defined MY_2ND_INTERPRETATION_OF_BOOK
  shared_ptr<ListNode<int>> even_dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, L});
  shared_ptr<ListNode<int>> odd_dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, nullptr});
  auto even_list_head = even_dummy_head;
  auto even_iter = even_dummy_head->next;
  auto odd_list_head = odd_dummy_head;

  unsigned long count = 0;
  while(even_iter) {
    if(count ^ 1) {
      even_iter = even_iter->next;
      even_list_head = even_list_head->next;
    }
    else {
      odd_list_head->next = even_iter;
      even_list_head->next = even_iter->next;
      even_iter->next = nullptr;
      even_iter = even_list_head->next;
    }
    count++;
  }
  even_list_head->next = odd_dummy_head->next;
  return even_dummy_head->next;
  
#else //The book did not explain this clearly.
  if (L == nullptr) {
    return L;
  }

  auto even_dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, nullptr}),
       odd_dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, nullptr});
  array<shared_ptr<ListNode<int>>, 2> tails = {even_dummy_head, odd_dummy_head};
  int turn = 0;
  for (auto iter = L; iter; iter = iter->next) {
    tails[turn]->next = iter;
    tails[turn] = tails[turn]->next;
    turn ^= 1;  // Alternate between even and odd.
  }
  tails[1]->next = nullptr;
  tails[0]->next = odd_dummy_head->next;
  return even_dummy_head->next;
#endif
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "even_odd_list_merge.cc",
                         "even_odd_list_merge.tsv", &EvenOddMerge,
                         DefaultComparator{}, param_names);
}
