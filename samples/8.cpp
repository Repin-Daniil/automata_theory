#include <cassert>
#include <iostream>

#include "automata/dfa/dfa.hpp"
#include "automata/nfa/nfa.hpp"
#include "grammar/grammar.hpp"

#include "utils/format/formatter.hpp"

int main() {
  using namespace lab::format;

  PrintHead("--- №8 ---");

  std::unordered_set<std::string> states = {"k1", "k2", "k3"};
  std::unordered_set<std::string> final_states = {"k3"};
  std::unordered_map<std::string, std::unordered_map<char, std::vector<std::string>>> transitions = {
    {"k1", {{'x', {"k1", "k2", "k3"}}, {'0', {}}}},
    {"k2", {{'x', {}}, {'0', {"k2", "k3"}}}},
    {"k3", {{'x', {"k3"}}, {'0', {}}}}
  };

  NFA nfa("k1", states, final_states, transitions);


  // DFA nfa = ConvertNfaToDfa(dfa);


  // assert(dfa.GenerateChains(10) == nfa.GenerateChains(10));
  // PrintTask("L(M) = L(M')", GetChains(dfa.GenerateChains(5)));

  // dfa.ToDot("dfa.dot");
  // PrintTask("Графическое представление: ", "dfa.dot");

  return EXIT_SUCCESS;
}

