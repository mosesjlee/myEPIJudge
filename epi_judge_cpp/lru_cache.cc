#include <vector>
#include <utility>
#include <list>
#include <unordered_map>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"

struct ISBNInfo {
  int price;
  bool recently_used;
};

class LruCache {
private:
  std::unordered_map<int, std::pair<std::list<int>::iterator, int>> ISBNRecords;
  std::list<int> lru_queue;
  size_t my_capacity;

  void MoveFront(int isbn, std::unordered_map<int, std::pair<std::list<int>::iterator, int>>::iterator it) {
    lru_queue.erase(it->second.first);
    lru_queue.emplace_front(isbn);
    it->second.first = lru_queue.begin();
  }

public:
  LruCache(size_t capacity) {
    my_capacity = capacity;
  }

  int Lookup(int isbn) {
    // TODO - you fill in here.
    auto it = ISBNRecords.find(isbn);
    if (it != ISBNRecords.end()) {
      MoveFront(isbn, it);
      return it->second.second;
    }
    else {
      return -1;
    }
  }
  void Insert(int isbn, int price) {
    // TODO - you fill in here.
    auto it = ISBNRecords.find(isbn);
    if(it != ISBNRecords.end()) {
      MoveFront(isbn, it);
    }
    else {
      if(ISBNRecords.size() == my_capacity) {
        //Kick out the least recently used
        ISBNRecords.erase(lru_queue.back());
        lru_queue.pop_back();
      }
      lru_queue.emplace_front(isbn);
      ISBNRecords[isbn] = {lru_queue.begin(), price};
    }
    return;
  }
  bool Erase(int isbn) {
    // TODO - you fill in here.
    auto it = ISBNRecords.find(isbn);
    if(it != ISBNRecords.end()) {
      lru_queue.erase(it->second.first);
      ISBNRecords.erase(isbn);
      return true;
    }
    else {
      return false;
    }
  }
};
struct Op {
  std::string code;
  int arg1;
  int arg2;
};

template <>
struct SerializationTraits<Op> : UserSerTraits<Op, std::string, int, int> {};

void RunTest(const std::vector<Op>& commands) {
  if (commands.empty() || commands[0].code != "LruCache") {
    throw std::runtime_error("Expected LruCache as first command");
  }
  LruCache cache(commands[0].arg1);

  for (int i = 1; i < commands.size(); i++) {
    auto& cmd = commands[i];
    if (cmd.code == "lookup") {
      int result = cache.Lookup(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Lookup: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else if (cmd.code == "insert") {
      cache.Insert(cmd.arg1, cmd.arg2);
    } else if (cmd.code == "erase") {
      bool result = cache.Erase(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Erase: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else {
      throw std::runtime_error("Unexpected command " + cmd.code);
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"commands"};
  return GenericTestMain(args, "lru_cache.cc", "lru_cache.tsv", &RunTest,
                         DefaultComparator{}, param_names);
}
