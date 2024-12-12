#include "dfa.hpp"

#include <fstream>

DFA::DFA(const std::string &start_id, const std::unordered_set<std::string> &states,
         const std::unordered_set<std::string> &final_states,
         const std::unordered_map<std::string, std::unordered_map<char, std::string> > &
         transitions) : Automata(start_id, states, final_states, TransformTransitions(transitions)) {
}


Language DFA::GenerateChains(std::size_t max_length) {
  Language language;
  std::queue<std::pair<std::string, std::shared_ptr<State> > > queue;

  queue.emplace(empty_chain, start_state_);

  while (!queue.empty()) {
    auto [current_chain, current_state] = queue.front();
    queue.pop();

    if (current_state->is_final) {
      language.insert(current_chain);
    }

    if (current_chain.size() < max_length) {
      for (const auto &[symbol, next_state]: current_state->transitions) {
        queue.emplace(current_chain + symbol, next_state.front());
      }
    }
  }

  return language;
}

std::unordered_map<std::string, std::unordered_map<char, std::vector<std::string> > > DFA::TransformTransitions(
  const std::unordered_map<std::string, std::unordered_map<char, std::string> > &transitions) {
  std::unordered_map<std::string, std::unordered_map<char, std::vector<std::string> > > result;
  for (const auto &[from, trans_map]: transitions) {
    for (const auto &[symbol, to]: trans_map) {
      result[from][symbol] = {to};
    }
  }
  return result;
}

bool DFA::Accept(std::string_view chain) {
  auto current_state = start_state_;
  for (char symbol: chain) {
    if (!current_state->transitions.contains(symbol) || current_state->transitions.at(symbol).empty()) {
      return false;
    }

    current_state = current_state->transitions.at(symbol).front();
  }
  return current_state->is_final;
}
