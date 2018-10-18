#include <string>
#include <unordered_map>
#include "test_framework/generic_test.h"
using std::string;
#define FIRST_ATTEMPT
//#define CLEANED_UP
bool IsLetterConstructibleFromMagazine(const string& letter_text,
                                       const string& magazine_text) {
  // TODO - you fill in here.
#ifdef FIRST_ATTEMPT
#pragma message ("FIRST ATTEMPT")
  std::unordered_map<char, int> magazine_letters;
  std::unordered_map<char, int> letter_letters;

  for(char c : magazine_text) {
    magazine_letters[c]++;
  }

  for(char c : letter_text) {
    letter_letters[c]++;
  }

  for(std::pair<char, int> letter : letter_letters) {
    if(!magazine_letters.count(letter.first) || 
        magazine_letters[letter.first] < letter.second) {
      return false;
    }
  }
#elif defined CLEANED_UP
#pragma message ("CLEANED UP ATTEMPT")
  std::unordered_map<char, int> magazine_letters;
  for(char c : magazine_text) {
    magazine_letters[c]++;
  }

  for(char c : letter_text) {
    magazine_letters[c]--;
    if(magazine_letters[c] < 0) {
      return false;
    }
  }
#else
#pragma message ("WAY OPTIMIZED FROM BOOK")
  std::unordered_map<char, int> letter_letters;
  for(char c : letter_text) {
    letter_letters[c]++;
  }

  for(char c : magazine_text) {
    auto it = letter_letters.find(c);
    if(it != letter_letters.end()) {
      it->second--;
      if(it->second == 0) {
        letter_letters.erase(it);
        if(letter_letters.empty()) {
          break;
        }
      }
    }
  }

  return letter_letters.empty();
#endif
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"letter_text", "magazine_text"};
  return GenericTestMain(args, "is_anonymous_letter_constructible.cc",
                         "is_anonymous_letter_constructible.tsv",
                         &IsLetterConstructibleFromMagazine,
                         DefaultComparator{}, param_names);
}
