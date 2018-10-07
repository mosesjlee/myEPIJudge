#include <string>
#include "test_framework/generic_test.h"
#include <stack>
using std::string;
bool IsWellFormed(const string& s) {
  // TODO - you fill in here.
  std::stack<char> expression;
  for(char paren : s) {  
    switch (paren) {
      case ')': {
        if(expression.empty() || expression.top() != '(') return false;
        expression.pop();
      }
      break;
      case '}': {
        if(expression.empty() || expression.top() != '{') return false;
        expression.pop();
      }
      break;
      case ']': {
        if(expression.empty() || expression.top() != '[') return false;
        expression.pop();
      }
      break;
      default:
        expression.push(paren);
      break;
    }
  }
  return expression.empty();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_valid_parenthesization.cc",
                         "is_valid_parenthesization.tsv", &IsWellFormed,
                         DefaultComparator{}, param_names);
}
