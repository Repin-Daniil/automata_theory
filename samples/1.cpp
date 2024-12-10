#include <iostream>

#include "grammar/grammar.hpp"
#include "utils/format/formatter.hpp"

int main() {
  using namespace lab::format;

  PrintHead("--- №1 ---");

  Alphabet alphabet = {'a', 'b'};
  Language language_1 = {"a", "aa", "baa"};
  Language language_2 = {"b", "aa", "abb"};

  PrintTask("L1 ∪ L2" ,GetChains(Union(language_1, language_2)));
  PrintTask("L1 ∩ L2", GetChains(Intersection(language_1, language_2)));

  PrintTask("L1 \\ L2", GetChains(Difference(language_1, language_2)));
  PrintTask("L2 \\ L1", GetChains(Difference(language_2, language_1)));

  PrintTask("L1L2", GetChains(Concatenation(language_1, language_2)));
  PrintTask("L2L1", GetChains(Concatenation(language_2, language_1)));

  PrintTask("L1'", GetChains(Complement(language_1, alphabet)));
  PrintTask("L2'", GetChains(Complement(language_2, alphabet)));

  return EXIT_SUCCESS;
}
