#include <iostream>

#include "automata/DFA/dfa.hpp"
#include "grammar/grammar.hpp"

#include "utils/format/formatter.hpp"

int main() {
  using namespace lab::format;

  PrintHead("--- №4 ---");

  std::unordered_set<std::string> states = {"S", "A", "B", "C"};
  std::unordered_set<std::string> final_states = {"C"};
  std::unordered_map<std::string, std::unordered_map<char, std::string> > transitions = {
    {"S", {{'a', "A"}}},
    {"A", {{'b', "B"}}},
    {"B", {{'b', "B"}, {'c', "C"}}},
    {"C", {{'c', "C"}}}
  };

  DFA dfa("S", states, final_states, transitions);

  auto chains = dfa.GenerateChains(5);
  PrintTask("L(M)", GetChains(chains));

  dfa.ToDot("dfa.dot");
  PrintTask("Графическое представление: ", "dfa.dot");

  return EXIT_SUCCESS;
}
