#include <iostream>

#include "grammar/grammar.hpp"

#include "utils/format/formatter.hpp"

int main() {
  using namespace lab::format;

  PrintHead("--- №10 ---");

  Grammar grammar_4(
    {
      {"S", {"a", "b", "c","aS","cS"}}
    },
    'S');

  PrintTask("L(G)", GetChains(grammar_4.GetChains(50)));

  return EXIT_SUCCESS;
}
