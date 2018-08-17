#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices) {
  // TODO - you fill in here.
	double curr_min = prices.front();
	double curr_profit = 0.0;
	for(int i = 1; i < prices.size(); i++) {
		curr_min = fmin(curr_min, prices[i]);
		curr_profit = fmax(prices[i] - curr_min, curr_profit);
	}

  return curr_profit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
