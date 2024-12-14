#include <iostream>

#include "automata/converter.hpp"
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

  PrintTask("L(G)", GetChains(grammar_4.GetChains(45)));
  auto nfa = GetNfaFromGrammar(grammar_4);

  PrintTask("L(G)", GetChains(nfa.GenerateChains(4)));


  nfa.ToDot("nfa.dot");
  PrintTask("Графическое представление: ", "nfa.dot");

  return EXIT_SUCCESS;
}
