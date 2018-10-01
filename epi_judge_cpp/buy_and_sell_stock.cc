#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices) {
  // TODO - you fill in here.
  double max_profit = 0.0;
#ifdef BRUTE_FORCE
  for(int i = 0; i < prices.size(); i++) {
    for(int j = i+1; j < prices.size(); j++) {
      max_profit = fmax(prices[j]-prices[i], max_profit);
    }
  }
#else
  double min_so_far = std::numeric_limits<double>::max();
  for(int i = 0; i < prices.size(); i++) {
    min_so_far = fmin(min_so_far, prices[i]);
    max_profit = fmax(prices[i] - min_so_far, max_profit);
  }
#endif
  return max_profit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
