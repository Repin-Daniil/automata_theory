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


  std::unordered_set<std::string> states_1 = {"{k1}", "{k1, k2, k3}", "{k2, k3}", "{k3}", "Ø"};
  std::unordered_set<std::string> final_states_1 = { "{k1, k2, k3}", "{k2, k3}","{k3}"};

  std::unordered_map<std::string, std::unordered_map<char, std::string>>  transitions_1= {
      {"{k1}", {{'x', "{k1, k2, k3}"}, {'0', "Ø"}}},
      {"{k1, k2, k3}", {{'x', "{k1, k2, k3}"}, {'0', "{k2, k3}"}}},
      {"{k2, k3}", {{'x', "{k3}"}, {'0', "{k2, k3}"}}},
      {"{k3}", {{'x', "{k3}"}, {'0', "Ø"}}},
      {"Ø", {{'x', "Ø"}, {'0', "Ø"}}}
  };

  DFA dfa("{k3}", states_1, final_states_1, transitions_1);

//  assert(dfa.GenerateChains(10) == nfa.GenerateChains(10));
  PrintTask("L(M) = L(M')", GetChains(dfa.GenerateChains(5)));
  PrintTask("L(M) = L(M')", GetChains(nfa.GenerateChains(5)));

  dfa.ToDot("dfa.dot");
  PrintTask("Графическое представление: ", "dfa.dot");

  return EXIT_SUCCESS;
}

