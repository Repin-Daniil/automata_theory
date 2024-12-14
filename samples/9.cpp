#include <iostream>

#include "automata/dfa/dfa.hpp"
#include "grammar/grammar.hpp"

#include "utils/format/formatter.hpp"

int main() {
  using namespace lab::format;
  using namespace std::literals;

  PrintHead("--- №9 ---");

  std::unordered_set states = {"S"s, "A"s, "B"s, "C"s};
  std::unordered_set final_states = {"C"s};
  std::unordered_map<std::string, std::unordered_map<char, std::string> > transitions = {
    {"S", {{'a', "A"}}},
    {"A", {{'b', "B"}}},
    {"B", {{'b', "B"}, {'c', "C"}}},
    {"C", {{'c', "C"}}}
  };

  DFA dfa("S", states, final_states, transitions);
  auto grammar_auto = dfa.GetRegularGrammar();

  PrintTask("L(G)", GetChains(grammar_auto.GetChains(20)));

  auto [Vn, Vt, S, P] = grammar_auto.GetFormalRepresentation();

  PrintTask("Vn", GetChains(Vn));


  std::set<std::string> Vt_str;

  for (const auto& terminal : Vt) {
    Vt_str.insert(std::string(1, terminal));
  }

  PrintTask("Vt", GetChains(Vt_str));
  PrintTask("S", std::string(1,S));

  std::stringstream ss_2;

  for (const auto& [lhs, rhs_set] : P) {
    for (const auto& rhs : rhs_set) {
      ss_2 << lhs << " -> " << rhs << "; ";
    }
  }

  PrintTask("P", "{" + ss_2.str() + "}");

  return EXIT_SUCCESS;
}
