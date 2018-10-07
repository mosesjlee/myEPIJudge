#include <string>
#include "test_framework/generic_test.h"
#include <stack>
using std::string;

int evaluated_expr(string & token, std::stack<int> * ref) {
  std::stack<int> & copy = *ref;
  if(token == "-") {
    int val_2 = copy.top(); copy.pop();
    int val_1 = copy.top(); copy.pop();
    return val_1-val_2;
  }
  else if(token == "+") {
    int val_2 = copy.top(); copy.pop();
    int val_1 = copy.top(); copy.pop();
    return val_1+val_2;
  }
  else if(token == "*") {
    int val_2 = copy.top(); copy.pop();
    int val_1 = copy.top(); copy.pop();
    return val_1 * val_2;
  }
  else if(token == "/") {
    int val_2 = copy.top(); copy.pop();
    int val_1 = copy.top(); copy.pop();
    return val_1/val_2;
  }
  else {
    return atoi(token.c_str());
  }
}

int Evaluate(const string& expression) {
  // TODO - you fill in here.
  std::stack<int> rpn;
  size_t start = 0;
  size_t comma_idx = 0;
  string token = "";
  while((comma_idx = expression.find(',', start)) != string::npos) {
    comma_idx = expression.find(',', start);
    token = expression.substr(start, comma_idx-start);
    rpn.push(evaluated_expr(token, &rpn));
    start = comma_idx + 1;
  }

  //Take care of the last expression
  token = expression.substr(start, expression.length()-start); 
  rpn.push(evaluated_expr(token, &rpn));
  return rpn.top();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"expression"};
  return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate,
                         DefaultComparator{}, param_names);
}
