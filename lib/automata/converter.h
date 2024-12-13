#pragma once
#include "dfa/dfa.hpp"
#include "nfa/nfa.hpp"

inline NFA ConvertDfaToNfa(DFA dfa) {
  dfa.Complete();

  return {dfa.GetStartState(), dfa.GetStates(), dfa.GetFinalStates(), dfa.GetTransitions()};
}


inline NFA GetNFA(Grammar grammar) {
  auto [Vn, Vt, S, P] = grammar.GetFormalRepresentation();

  //FIXME проверить на отсутствие пустой цепочки

  std::unordered_set<std::string> states(Vn.begin(), Vn.end());
  states.insert(dummy_symbol);

  std::unordered_map<std::string, std::unordered_map<char, std::vector<std::string>>> transitions;

  // Заполнение переходов по продукциям
  for (const auto &[non_terminal, rules] : P) {
    for (const auto &rule : rules) {
      if (rule.size() == 2 && std::isupper(rule[1])) { // Продукция A -> aB
        char symbol = rule[0];
        std::string next_state = std::string(1, rule[1]);

        transitions[non_terminal][symbol].push_back(next_state);
      } else if (rule.size() == 1) { // Продукция A -> a
        char symbol = rule[0];
        transitions[non_terminal][symbol].push_back(dummy_symbol);
      }
    }
  }

  NFA nfa(std::string(1, S), states, {dummy_symbol}, transitions);

  return nfa;
}