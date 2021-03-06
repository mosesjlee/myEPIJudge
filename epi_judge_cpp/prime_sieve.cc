#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
// Given n, return all primes up to and including n.
vector<int> GeneratePrimes(int n) {
  // TODO - you fill in here.
  vector<int> sieve(n+1, 1);
  vector<int> result;


  for(int i = 2; i < sieve.size(); i++) {
    if(sieve[i] == 1) { //Why double check if it's already marked prime?
      for(int j = 2; j * i < sieve.size(); j++) {
          sieve[j*i] = 0;
      }
    }
  }

  for(int i = 2; i < sieve.size(); i++) {
    if(sieve[i] == 1)
      result.push_back(i);
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                         &GeneratePrimes, DefaultComparator{}, param_names);
}
