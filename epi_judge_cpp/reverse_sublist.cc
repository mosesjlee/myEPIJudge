#include "list_node.h"
#include "test_framework/generic_test.h"
//#define BRUTE_FORCE
//#define BRUTE_FORCE_2 //DOESNT WORK
void ReverseList(shared_ptr<ListNode<int>> prev_start, shared_ptr<ListNode<int>> & start, shared_ptr<ListNode<int>> & end );
void ReverseList2(shared_ptr<ListNode<int>> & prev_start, shared_ptr<ListNode<int>> & start, shared_ptr<ListNode<int>> & end, int count );

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {
  // TODO - you fill in here.
  if(start == finish) return L;
#ifdef BRUTE_FORCE
  shared_ptr<ListNode<int>> prev = nullptr, start_node = L, end_node = L, traveler = L;
  for(int i = 1; i <= finish; i++) {
    if(i == start -1) prev = traveler;
    if(i == start) start_node = traveler;
    if(i == finish) end_node = traveler;
    traveler = traveler->next;
  }

  ReverseList(prev, start_node, end_node);
  if(prev) prev->next = start_node;
  else L = start_node;
  return L;

#elif defined BRUTE_FORCE_2
  auto prev = make_shared<ListNode<int>>(ListNode<int>{0, L}), start_node = L, end_node = L, traveler = L;
  for(int i = 1; i <= finish; i++) {
    if(i == start -1) prev = traveler;
    if(i == start) start_node = traveler;
    if(i == finish) end_node = traveler;
    traveler = traveler->next;
  }

  ReverseList2(prev, start_node, end_node, finish-start);

  return prev->next;
#elif defined BOOK_LOGIC
  //This is the book's implementation. Very clean, but need to work on pointer
  //Logic
  auto dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, L});
  auto sublist_head = dummy_head;
  int k = 1;

  while (k++ < start) {
    sublist_head = sublist_head->next;
  }

  auto sublist_iter = sublist_head->next;
  while(start++ < finish) {
    auto temp = sublist_iter->next;
    sublist_iter->next = temp->next;
    temp->next = sublist_head->next;
    sublist_head->next = temp;
  }
  return dummy_head->next;
#else
#pragma message("MY NEW UPDATED ATTEMPT")
  auto dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, L});
  auto head = dummy_head;
  auto master_iter = L;
  int k = 1;

  while(k++ < start) {
    head = head->next;
  }

  auto iter = head->next;

  while(start++ < finish) {
    auto temp = iter->next;
    iter->next = temp->next;
    temp->next = head->next;
    head->next = temp;
  }
 
  return dummy_head->next;
#endif
}

void ReverseList2(shared_ptr<ListNode<int>> * prev_start, shared_ptr<ListNode<int>> * start, shared_ptr<ListNode<int>> *end, int count ) {
  shared_ptr<ListNode<int>> prev = *prev_start, curr = prev->next, temp = nullptr;
  while(count--) {
    //Update pointers
    temp = curr->next;
    curr->next = temp->next;
    temp->next = prev->next;
    prev->next = temp;
  } 
}

void ReverseList(shared_ptr<ListNode<int>> prev_start, shared_ptr<ListNode<int>> & start, shared_ptr<ListNode<int>> & end ) {
  shared_ptr<ListNode<int>> prev = prev_start, curr = start, temp = nullptr;
  while(curr && prev != end) {
    //Update pointers
    temp = curr->next;
    curr->next = prev;
    prev = curr;
    curr = temp;
  }
  if(prev_start) prev_start->next = prev;
  start->next = curr;
  start = prev;
}



int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "start", "finish"};
  return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                         &ReverseSublist, DefaultComparator{}, param_names);
}
