#include <assert.h>
#include <iostream>

#include "../lib/automata/converter.hpp"
#include "automata/dfa/dfa.hpp"
#include "automata/nfa/nfa.hpp"
#include "grammar/grammar.hpp"

#include "utils/format/formatter.hpp"

int main() {
  using namespace lab::format;
  using namespace std::literals;

  PrintHead("--- №7 ---");

  std::unordered_set states = {"S"s, "A"s, "B"s, "C"s};
  std::unordered_set final_states = {"C"s};
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
