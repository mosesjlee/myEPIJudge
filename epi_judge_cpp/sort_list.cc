#include <memory>
#include "list_node.h"
#include "test_framework/generic_test.h"
#define main _main
#include "sorted_lists_merge.cc"
#undef main
shared_ptr<ListNode<int>> StableSortList(shared_ptr<ListNode<int>> L) {
  // TODO - you fill in here.
#ifdef BOOK_BRUTE_FORCE
  shared_ptr<ListNode<int>> dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, L});
  shared_ptr<ListNode<int>> iter = L;

  while(iter && iter->next) {
    if(iter->data > iter->next->data) {
      shared_ptr<ListNode<int>> target = iter->next; shared_ptr<ListNode<int>> pre = dummy_head;
      while(pre->next->data < target->data) {
        pre = pre->next;
      }
      shared_ptr<ListNode<int>> temp = pre->next;
      pre->next = target;
      iter->next = target->next;
      target->next = temp;

    }
    else {
      iter = iter->next;
    }
  }

  return dummy_head->next;
#elif defined MY_BRUTE_FORCE
  shared_ptr<ListNode<int>> dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, nullptr});
  shared_ptr<ListNode<int>> iter = L;
#else
  if (L == nullptr || L->next == nullptr) {
    return L;
  }

  shared_ptr<ListNode<int>> pre_slow = nullptr;
  shared_ptr<ListNode<int>> slow = L;
  shared_ptr<ListNode<int>> fast = L;

  while(fast && fast->next) {
    pre_slow = slow;
    slow = slow->next;
    fast = fast->next->next;
  }

  pre_slow->next = nullptr;

  return MergeTwoSortedLists(StableSortList(L), StableSortList(slow));
#endif  
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "sort_list.cc", "sort_list.tsv", &StableSortList,
                         DefaultComparator{}, param_names);
}
