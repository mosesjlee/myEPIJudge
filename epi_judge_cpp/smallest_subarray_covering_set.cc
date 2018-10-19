#include <string>
#include <unordered_set>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::unordered_set;
using std::vector;
#define BRUTE_FORCE

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
  Subarray retval = {0,0};
  int shortest = INT_MAX;
  std::unordered_set<string> word_set;
  int end_idx = 0;

  for(int i = end_idx; i < paragraph.size(); i++) {
    for(string s : keywords) {
      word_set.insert(s);
    }
    for(int j = i; j < paragraph.size(); j++) {
      if(word_set.count(paragraph[j])) {
        word_set.erase(paragraph[j]);
      }

      if(word_set.empty()) {
        int dist = end_idx-i;
        if(dist < shortest) {
          shortest = dist;
          retval.start = i;
          retval.end = end_idx;
        }
        break;
      }
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
