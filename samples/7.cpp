#include <assert.h>
#include <iostream>

#include "../lib/automata/converter.h"
#include "automata/dfa/dfa.hpp"
#include "automata/nfa/nfa.hpp"
#include "grammar/grammar.hpp"

#include "utils/format/formatter.hpp"

int main() {
  using namespace lab::format;

  PrintHead("--- №7 ---");

  std::unordered_set<std::string> states = {"S", "A", "B", "C"};
  std::unordered_set<std::string> final_states = {"C"};
  std::unordered_map<std::string, std::unordered_map<char, std::string> > transitions = {
    {"S", {{'a', "A"}}},
    {"A", {{'b', "B"}}},
    {"B", {{'b', "B"}, {'c', "C"}}},
    {"C", {{'c', "C"}}}
  };

  DFA dfa("S", states, final_states, transitions);

  NFA nfa = ConvertDfaToNfa(dfa);


  assert(dfa.GenerateChains(10) == nfa.GenerateChains(10));
  PrintTask("L(M) = L(M')", GetChains(nfa.GenerateChains(5)));

  nfa.ToDot("nfa.dot");
  PrintTask("Графическое представление: ", "nfa.dot");

  return EXIT_SUCCESS;
}
