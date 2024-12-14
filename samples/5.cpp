#include <iostream>

#include "automata/dfa/dfa.hpp"
#include "grammar/grammar.hpp"

#include "utils/format/formatter.hpp"

int main() {
  using namespace lab::format;
  using namespace std::literals;

  PrintHead("--- №5 ---");

  std::unordered_set states = {"S"s, "A"s, "B"s, "C"s};
  std::unordered_set final_states = {"C"s};
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
