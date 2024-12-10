#include <iostream>

#include "grammar/grammar.hpp"

#include "utils/format/formatter.hpp"

int main() {
  using namespace lab::format;

  PrintHead("--- №4 ---");

  Grammar grammar_4(
    {
      {"S", {"", "A", "B"}},
      {"A", {"0A", "0"}},
      {"B", {"1B", "1"}}
    },
    'S');

  PrintTask("L(G)" , GetChains(grammar_4.GetChains(20)));

  return EXIT_SUCCESS;
}
