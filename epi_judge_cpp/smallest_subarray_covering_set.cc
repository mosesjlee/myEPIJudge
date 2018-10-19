#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::unordered_set;
using std::vector;
//#define BRUTE_FORCE

struct Subarray {
  int start, end;
};

Subarray FindSmallestSubarrayCoveringSet(
    const vector<string> &paragraph, const unordered_set<string> &keywords) {
  // TODO - you fill in here.
#ifdef BRUTE_FORCE
#pragma message ("BRUTE FORCE")
  Subarray retval = {0,0};
  int shortest = INT_MAX;
  std::unordered_set<string> word_set;

  for(int i = 0; i < paragraph.size(); i++) {
    for(string s : keywords) {
      word_set.insert(s);
    }
    for(int j = i; j < paragraph.size(); j++) {
      if(word_set.count(paragraph[j])) {
        word_set.erase(paragraph[j]);
      }
      if(word_set.empty()) {
        int dist = j-i;
        if(dist < shortest) {
          shortest = dist;
          retval.start = i;
          retval.end = j;
        }
        break;
      }
    }
  }

  return retval;
#else
#pragma message ("ATTEMPT TO OPTIMIZE FORCE")
  Subarray retval = {-1,-1};
  int num_of_keywords = keywords.size();
  std::unordered_map<string, int> keyword_set;
  for(string s : keywords) {
    keyword_set[s] = 1;
  }
  int shortest = INT_MAX;
  int look_ahead = 0; int catch_up = 0;
  for(; look_ahead < paragraph.size(); look_ahead++) {
    if(keyword_set.count(paragraph[look_ahead])) {
      //If found decrement it to keep track of
      //this key found
      keyword_set[paragraph[look_ahead]]--;

      //Only say that we found it and increment it
      //when we see the first instance
      if(keyword_set[paragraph[look_ahead]] == 0)
        num_of_keywords--;
    }

    while(0 == num_of_keywords) {
      
      if(keyword_set.count(paragraph[catch_up])) {
        if(keyword_set[paragraph[catch_up]] < 1) {
          keyword_set[paragraph[catch_up]]++;

          //If its the last in this set we have to look
          //For another 1
          if(keyword_set[paragraph[catch_up]] == 1) {
            num_of_keywords++;
          }
        }

        if((look_ahead-catch_up) < shortest) {
          shortest = (look_ahead-catch_up);
          retval.start = catch_up;
          retval.end = look_ahead;
        }
      }
      catch_up++;
    } 
  }
  return retval;
#endif  
}
int FindSmallestSubarrayCoveringSetWrapper(
    TimedExecutor &executor, const vector<string> &paragraph,
    const unordered_set<string> &keywords) {
  unordered_set<string> copy = keywords;

  auto result = executor.Run(
      [&] { return FindSmallestSubarrayCoveringSet(paragraph, keywords); });

  if (result.start < 0 || result.start >= paragraph.size() || result.end < 0 ||
      result.end >= paragraph.size() || result.start > result.end) {
    throw TestFailure("Index out of range");
  }

  for (int i = result.start; i <= result.end; i++) {
    copy.erase(paragraph[i]);
  }

  if (!copy.empty()) {
    throw TestFailure("Not all keywords are in the range");
  }

  return result.end - result.start + 1;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "paragraph", "keywords"};
  return GenericTestMain(args, "smallest_subarray_covering_set.cc",
                         "smallest_subarray_covering_set.tsv",
                         &FindSmallestSubarrayCoveringSetWrapper,
                         DefaultComparator{}, param_names);
}
