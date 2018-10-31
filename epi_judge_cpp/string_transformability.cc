#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "test_framework/generic_test.h"
using std::string;
using std::unordered_set;
#define BRUTE_FORCE

bool OnlyOneCharDiff(string s1, string s2) {
  if(s1.length() != s2.length() || s1 == s2) return false;

  int diff = 0;
  for(int i = 0; i < s1.length(); i++) {
    if(s1[i] != s2[i]) {
      diff++;
    }
  }

  return diff == 1;
}

void InsertToGraph(std::unordered_map<string, unordered_set<string>> * graph, string val1, string val2) {
  (*graph)[val1].insert(val2);
  (*graph)[val2].insert(val1);
}

struct DistanceFromStart {
  string str;
  int distance;
};

// Uses BFS to find the least steps of transformation.
int TransformString(unordered_set<string> D, const string& s, const string& t) {
  // TODO - you fill in here.
#ifdef BRUTE_FORCE
  std::unordered_map<string, unordered_set<string>> word_graph;
  unordered_set<string> D_copy(D);
  for(auto iter = D.begin(); iter != D.end(); iter++) {
    word_graph[*iter] = {};
    // D_copy.erase(*iter);
    for(auto iterDest = D_copy.begin(); iterDest != D_copy.end(); iterDest++) {
      if(OnlyOneCharDiff(*iter, *iterDest)) {
        InsertToGraph(&word_graph, *iter, *iterDest);
      }
    }
  }

  std::queue<DistanceFromStart> to_visit_queue;
  to_visit_queue.emplace(DistanceFromStart{s, 0});
  
  while(!to_visit_queue.empty()) {
    auto curr = to_visit_queue.front();
    if(curr.str == t) {
      return curr.distance;
    }
    D.erase(curr.str);
    to_visit_queue.pop();
    
    auto my_nodes = word_graph[curr.str];
    
    // std::cout << curr.str << " has " << my_nodes.size() << " child " << std::endl;
    for(auto iter = my_nodes.begin(); iter != my_nodes.end(); iter++) {

      if(D.count(*iter)) {
        to_visit_queue.emplace(DistanceFromStart{(*iter), curr.distance+1});
      }
    }
  }

  return - 1;
#else

#pragma message ("OPTIMIZED WITH BOOK")
  std::queue<DistanceFromStart> to_visit_queue;
  to_visit_queue.emplace(DistanceFromStart{s, 0});
  D.erase(s);
  
  while(!to_visit_queue.empty()) {
    auto curr = to_visit_queue.front();
    if(curr.str == t) {
      return curr.distance;
    }
    D.erase(curr.str);
    to_visit_queue.pop();
    
    string str = curr.str;
    for(int i = 0; i < str.length(); i++) {
      for(int j = 0; j < 26; j++) {
        str[i] = 'a' + j;
        auto it = D.find(str);
        if(it != D.end()) {
          to_visit_queue.emplace(DistanceFromStart{str, curr.distance+1});
        }
      }
      str[i] = curr.str[i];
    }
  }

  return -1;
#endif
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"D", "s", "t"};
  return GenericTestMain(args, "string_transformability.cc",
                         "string_transformability.tsv", &TransformString,
                         DefaultComparator{}, param_names);
}
