#include <iostream>

#include "grammar/grammar.hpp"

#include "utils/format/formatter.hpp"

int main() {
  using namespace lab::format;

  PrintHead("--- №3 ---");

  Grammar grammar({
                    {"S", {"abcA"}},
                    {"A", {"bbbS", ""}}
                  },
                  'S');


  PrintTask("L(G)", PrintLanguage(grammar.GetChains(10)));

  return EXIT_SUCCESS;
}
