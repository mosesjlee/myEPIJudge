#include <stdexcept>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include <stack>
#include <tuple>
using std::length_error;

class Stack {
  std::stack<std::tuple<int,int>> storage;
  int max_val = INT_MIN;
public:
  bool Empty() const {
    // TODO - you fill in here.
    return storage.empty();
  }
  int Max() const {
    // TODO - you fill in here.
    if(storage.empty()) {
      throw length_error("EMPTY STACK");
    }
    return max_val;
  }
  int Pop() {
    // TODO - you fill in here.
    std::tuple<int, int> popped = storage.top();
    storage.pop();
    int retval = std::get<0>(popped);
    int cached_max = std::get<1>(popped);
    if(retval == max_val) {
      max_val = cached_max;
    }
    return retval;
  }
  void Push(int x) {
    // TODO - you fill in here.
    storage.push(std::make_tuple(x, max_val));
    max_val = fmax(max_val, x);
    return;
  }
};
struct StackOp {
  std::string op;
  int argument;
};

template <>
struct SerializationTraits<StackOp> : UserSerTraits<StackOp, std::string, int> {
};

void StackTester(const std::vector<StackOp>& ops) {
  try {
    Stack s;
    for (auto& x : ops) {
      if (x.op == "Stack") {
        continue;
      } else if (x.op == "push") {
        s.Push(x.argument);
      } else if (x.op == "pop") {
        int result = s.Pop();
        if (result != x.argument) {
          throw TestFailure("Pop: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else if (x.op == "max") {
        int result = s.Max();
        if (result != x.argument) {
          throw TestFailure("Max: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else if (x.op == "empty") {
        int result = s.Empty();
        if (result != x.argument) {
          throw TestFailure("Empty: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else {
        throw std::runtime_error("Unsupported stack operation: " + x.op);
      }
    }
  } catch (length_error&) {
    throw TestFailure("Unexpected length_error exception");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "stack_with_max.cc", "stack_with_max.tsv",
                         &StackTester, DefaultComparator{}, param_names);
}
