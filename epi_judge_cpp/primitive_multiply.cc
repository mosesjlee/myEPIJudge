#include "test_framework/generic_test.h"

//THIS IS CHEATING!!! i used the "++" operator in this implementation
unsigned long long addCheating(unsigned long long x, unsigned long long y) {
  unsigned long long result = 0;
  int shift_count = 0;

  //THESE USED TO BE INT BUT I RAN INTO INTEGER OVERFLOW USE LONG IF SPECIFIED LONG
  long long curr_x_bit = 0, curr_y_bit = 0;
  long long added_bit = 0, carry_over = 0;
  while(x != 0 || y != 0) {
    curr_x_bit = x & 1;
    curr_y_bit = y & 1;
    added_bit = curr_x_bit ^ curr_y_bit ^ carry_over;
    carry_over = (curr_x_bit & curr_y_bit) | (curr_x_bit & carry_over) | (curr_y_bit & carry_over);
    result |= (added_bit << shift_count);
    x >>= 1; y >>= 1;
    shift_count++; //CHEATING!!!
  }

  return result |= (carry_over << shift_count);
}

unsigned long long add(unsigned long long x, unsigned long long y) {
  unsigned long long result = 0;
  long long shifter = 1;
  long long curr_x_bit = 0, curr_y_bit = 0, temp_x = x, temp_y = y;
  long long carry_over = 0, carry_in = 0;

  while(temp_x || temp_y) {
    curr_x_bit = x & shifter;
    curr_y_bit = y & shifter;
    carry_over = (curr_x_bit & curr_y_bit) | (curr_x_bit & carry_in) | (curr_y_bit & carry_in);
    result |= curr_x_bit ^ curr_y_bit ^ carry_in;
    carry_in = carry_over << 1; 
    temp_y >>= 1;
    temp_x >>= 1;
    shifter <<= 1; 
  }

  return result |= carry_in;
}

unsigned long long Multiply(unsigned long long x, unsigned long long y) {
  // TODO - you fill in here.
// #define BRUTE_FORCE
#ifdef BRUTE_FORCE
  if(x == 0 || y == 0) return 0;
  unsigned long long result = 0;
  unsigned int start = 0;
  while(start < y) {
    result += add(x, 0);
    start++;
  }
#else
  long long result = 0;
  while(x) {
    if(x & 1) {
      result = add(result, y);
    }
    x >>= 1; y <<= 1;
  }
#endif
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "primitive_multiply.cc",
                         "primitive_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
