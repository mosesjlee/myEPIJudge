#include "list_node.h"
#include "test_framework/generic_test.h"


void PrintList(shared_ptr<ListNode<int>> L) {
  std::cout << "NEW LIST\n";
  while(L) {
    std::cout << L->data << std::endl;
    L = L->next;
  }
}


shared_ptr<ListNode<int>> ReverseList(shared_ptr<ListNode<int>> L) {
  auto dummy_head = make_shared<ListNode<int>>(ListNode<int>{INT_MIN, nullptr});
  auto iter = L;

  while(iter) {
    auto temp = dummy_head->next;
    dummy_head->next = iter;
    iter = iter->next;
    dummy_head->next->next = temp;
  }
  return dummy_head->next;
}

bool IsLinkedListAPalindrome(shared_ptr<ListNode<int>> L) {
  // TODO - you fill in here.
  auto slow = L, fast = L;
  while(fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }

  fast = ReverseList(slow);
  auto iter = L;
   

  while(iter && fast) {
    if(iter->data != fast->data) {
      return false;
    }
    iter = iter->next;
    fast = fast->next;
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "is_list_palindromic.cc",
                         "is_list_palindromic.tsv", &IsLinkedListAPalindrome,
                         DefaultComparator{}, param_names);
}
