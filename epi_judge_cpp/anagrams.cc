#include <string>
#include <vector>
#include <unordered_map>
#include "test_framework/generic_test.h"
using std::string;
using std::vector;

vector<vector<string>> FindAnagrams(const vector<string>& dictionary) {
  // TODO - you fill in here.
  std::unordered_map<string, vector<string>> hash_table;
  vector<vector<string>> retval;

  for(string s : dictionary) {
    string sorted_word = s;
    std::sort(sorted_word.begin(), sorted_word.end());
    hash_table[sorted_word].push_back(s);
  }

  for(std::pair<string, vector<string>> item : hash_table) {
    if(item.second.size() < 2) continue;
    retval.push_back(item.second);
  }
  return retval;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"dictionary"};
  return GenericTestMain(
      args, "anagrams.cc", "anagrams.tsv", &FindAnagrams,
      &UnorderedComparator<std::vector<std::vector<std::string>>>, param_names);
}
