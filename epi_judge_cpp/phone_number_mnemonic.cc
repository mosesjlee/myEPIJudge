#include <string>
#include <vector>
#include "test_framework/generic_test.h"
using std::string;
using std::vector;

#define FROM_THE_BACK
// #define FROM_THE_FRONT

vector<vector<string>> phone_pad = {{"0"}, 
                                   {"1"}, {"A","B","C"}, {"D", "E", "F"}, 
                                   {"G", "H", "I"}, {"J","K","L"}, {"M", "N", "O"}, 
                                   {"P", "Q", "R", "S"}, {"T","U","V"}, {"W", "X", "Y", "Z"}};
vector<string> PhoneMnemonic(const string& phone_number) {
  // TODO - you fill in here.
#ifdef FROM_THE_BACK
  if(phone_number == "") return {};
  
  vector<string> words_so_far = PhoneMnemonic(phone_number.substr(1, phone_number.length()));

  int index = phone_number[0] - '0';
  // std::cout << "my number " << phone_number[0] << std::endl;
  if(words_so_far.size() == 0) return phone_pad[index];

  vector<string> retval;
    for(string s : words_so_far) {
      for(string my_c : phone_pad[index]) {
      retval.push_back(std::string(my_c+s));
    }
  }
  return retval;
#elif defined FROM_THE_FRONT

  if(phone_number == "") return {};
  
  vector<string> words_so_far = PhoneMnemonic(phone_number.substr(0, phone_number.length()-1));

  int index = phone_number[phone_number.length()-1] - '0';
  // std::cout << "my number " << phone_number[phone_number.length()-1] << std::endl;
  if(words_so_far.size() == 0) return phone_pad[index];

  vector<string> retval;
    for(string s : words_so_far) {
      for(string my_c : phone_pad[index]) {
      retval.push_back(std::string(s+my_c));
    }
  }
  return retval;
#endif
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"phone_number"};
  return GenericTestMain(args, "phone_number_mnemonic.cc",
                         "phone_number_mnemonic.tsv", &PhoneMnemonic,
                         &UnorderedComparator<std::vector<std::string>>,
                         param_names);
}
