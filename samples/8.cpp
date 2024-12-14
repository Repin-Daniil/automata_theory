#include <cassert>
#include <iostream>

#include "automata/dfa/dfa.hpp"
#include "automata/nfa/nfa.hpp"
#include "grammar/grammar.hpp"

#include "utils/format/formatter.hpp"

int main() {
  using namespace lab::format;
  using namespace std::literals;

  PrintHead("--- №8 ---");

  std::unordered_set states = {"k1"s, "k2"s, "k3"s};
  std::unordered_set final_states = {"k3"s};
  std::unordered_map<std::string, std::unordered_map<char, std::vector<std::string>>> transitions = {
    {"k1", {{'x', {"k1", "k2", "k3"}}, {'0', {}}}},
    {"k2", {{'x', {}}, {'0', {"k2", "k3"}}}},
    {"k3", {{'x', {"k3"}}, {'0', {}}}}
  };

  NFA nfa("k1", states, final_states, transitions);


  std::unordered_set states_1 = {"{k1}"s, "{k1, k2, k3}"s, "{k2, k3}"s, "{k3}"s, "Ø"s};
  std::unordered_set final_states_1 = { "{k1, k2, k3}"s, "{k2, k3}"s,"{k3}"s};

  std::unordered_map<std::string, std::unordered_map<char, std::string>>  transitions_1= {
      {"{k1}", {{'x', "{k1, k2, k3}"}, {'0', "Ø"}}},
      {"{k1, k2, k3}", {{'x', "{k1, k2, k3}"}, {'0', "{k2, k3}"}}},
      {"{k2, k3}", {{'x', "{k3}"}, {'0', "{k2, k3}"}}},
      {"{k3}", {{'x', "{k3}"}, {'0', "Ø"}}},
      {"Ø", {{'x', "Ø"}, {'0', "Ø"}}}
  };

  DFA dfa("{k1}", states_1, final_states_1, transitions_1);

  assert(dfa.GenerateChains(10) == nfa.GenerateChains(10));
  PrintTask("L(M')", GetChains(dfa.GenerateChains(5)));
  PrintTask("L(M)", GetChains(nfa.GenerateChains(5)));

  dfa.ToDot("dfa.dot");
  PrintTask("Графическое представление: ", "dfa.dot");

  return EXIT_SUCCESS;
}

