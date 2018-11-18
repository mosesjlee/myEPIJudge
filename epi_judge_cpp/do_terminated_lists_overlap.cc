#include <memory>
#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::shared_ptr;

shared_ptr<ListNode<int>> OverlappingNoCycleLists(
    shared_ptr<ListNode<int>> l0, shared_ptr<ListNode<int>> l1) {
  // TODO - you fill in here.
#ifdef FIRST_ATTEMPT
  if(l0 == nullptr && l1 == nullptr) {
    return nullptr;
  }

  shared_ptr<ListNode<int>> L0_header = l0, L1_header = l1;
  long L0_length = 0, L1_length = 0; 
  while(L0_header && L0_header->next) {
    L0_header = L0_header->next;
    L0_length++;
  }

  while(L1_header && L1_header->next) {
    L1_header = L1_header->next;
    L1_length++;
  }

  if(L0_header == L1_header) {
    L0_header = l0; L1_header = l1;
    long l0_length_copy = L0_length; long l1_length_copy = L1_length;
    if(L0_length > L1_length) {
      while(l0_length_copy-- > L1_length) {
        L0_header = L0_header->next;
      }
    }

    if(L1_length > L0_length) {
      while(l1_length_copy-- > L0_length) {
        L1_header = L1_header->next;
      }
    }

    while(L1_header != L0_header) {
      L0_header = L0_header->next;
      L1_header = L1_header->next;
    }

    return L1_header;
  }

  return nullptr;
#else
  if(l0 == nullptr && l1 == nullptr) {
    return nullptr;
  }

  shared_ptr<ListNode<int>> L0_header = l0, L1_header = l1;
  long L0_length = 0, L1_length = 0; 
  while(L0_header && L0_header->next) {
    L0_header = L0_header->next;
    L0_length++;
  }

  while(L1_header && L1_header->next) {
    L1_header = L1_header->next;
    L1_length++;
  }

  L0_header = l0, L1_header = l1;

  
#endif
}
void OverlappingNoCycleListsWrapper(TimedExecutor& executor,
                                    shared_ptr<ListNode<int>> l0,
                                    shared_ptr<ListNode<int>> l1,
                                    shared_ptr<ListNode<int>> common) {
  if (common) {
    if (l0) {
      auto i = l0;
      while (i->next) {
        i = i->next;
      }
      i->next = common;
    } else {
      l0 = common;
    }

    if (l1) {
      auto i = l1;
      while (i->next) {
        i = i->next;
      }
      i->next = common;
    } else {
      l1 = common;
    }
  }

  auto result = executor.Run([&] { return OverlappingNoCycleLists(l0, l1); });

  if (result != common) {
    throw TestFailure("Invalid result");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "l0", "l1", "common"};
  return GenericTestMain(
      args, "do_terminated_lists_overlap.cc", "do_terminated_lists_overlap.tsv",
      &OverlappingNoCycleListsWrapper, DefaultComparator{}, param_names);
}
