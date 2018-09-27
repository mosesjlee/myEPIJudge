#include "test_framework/generic_test.h"
int Divide(int x, int y) {
  // TODO - you fill in here.
  //my version.
  //CAN'T USE * or /
  //I had to break it down because the books way used bit manipulation
  //That is not very obvious. My comments show where i correlated the 
  //Concepts in the book
  //Have to commit memory that 2^k is equivallent to 1 << k
  //Have to commit memory that 2^k * k is equivallent to k << k
  
  long power = 32; //Limit to 32 to prevent overflow
  unsigned long y_power = (long) y << power; //To simulate 2 ^ k * y where k == y 
  long quotient = 0;
  long x_cast = (long) x;
  long y_cast = (long) y; 
  while (x_cast >= y_cast) {
    if(y_power <= x_cast) {
      x_cast -= y_power;
      quotient += 1 << power; //To simulate quotient += 2 ^ k
    }
    else {
      y_power >>= 1;
      power--;
    }
  }
  return quotient;
}

  // int quotient = 0;
  // while (x >= y) {
  //   while(y_power > x) {
  //     y_power >>= 1;
  //     power--;
  //   }

  //   x -= y_power;
  //   quotient += 1 << power;
  // }
  // return quotient;

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "primitive_divide.cc", "primitive_divide.tsv",
                         &Divide, DefaultComparator{}, param_names);
}
