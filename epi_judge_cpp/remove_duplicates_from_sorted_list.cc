#include <memory>
#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;
// #define DUMMY_HEAD
shared_ptr<ListNode<int>> RemoveDuplicates(const shared_ptr<ListNode<int>>& L) {
  // TODO - you fill in here.
#ifdef DUMMY_HEAD
  shared_ptr<ListNode<int>> dummy_head = make_shared<ListNode<int>>(ListNode<int>{INT_MIN, nullptr});
  auto tail = dummy_head;
  auto iter = L;

  while(iter) {
    if(iter->data != tail->data) {
      tail->next = iter;
      tail = tail->next;
    }
    //If Shared pointer wasn't used delete the duplicate node
    //Code would follow this structure
    /*
    if(iter->data != tail->data) {
      tail->next = iter;
      tail = tail->next;
      iter = iter->next;
    }
    else {
      Node * temp = iter;
      iter = iter->next;
      delete temp;
    }
    */
    iter = iter->next;
  }
  tail->next = nullptr;
  return dummy_head->next;
#else
  auto iter = L;

  while(iter && iter->next) {
    if(iter->data == iter->next->data) {
      iter->next = iter->next->next;
      //If Shared pointer wasn't used delete the duplicate node
      //DELETE DUPLICATE NODE
    } 
    else {
      iter = iter->next;
    }
  }
  return L;
#endif
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "remove_duplicates_from_sorted_list.cc",
                         "remove_duplicates_from_sorted_list.tsv",
                         &RemoveDuplicates, DefaultComparator{}, param_names);
}
