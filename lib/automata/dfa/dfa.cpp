#include "dfa.hpp"

#include <fstream>

#include "grammar/grammar.hpp"
#include <memory>

DFA::DFA(const std::string &start_id, const std::unordered_set<std::string> &states,
         const std::unordered_set<std::string> &final_states,
         const std::unordered_map<std::string, std::unordered_map<char, std::string> > &
         transitions, Alphabet alphabet) : Automata(start_id, states, final_states,
                                                    TransformTransitions(transitions), std::move(alphabet)) {
}

//TODO Консистентно должно быть, либо везде по ссылке, либо по значению с мувом

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

Grammar DFA::GetRegularGrammar() {
  if (GenerateChains(1).contains(empty_chain)) {
    //FIXME нужно другой алгоритм уже примнеять, как в методичке описано в одной з теорем
  }

  Productions productions;

  for (const auto &[state_id, state]: states_map_) {
    std::string non_terminal = state_id;

    for (const auto &[symbol, next_states]: state->transitions) {
      for (const auto &next_state: next_states) {
        std::string next_non_terminal = next_state->id;
        productions[non_terminal].insert(symbol + next_non_terminal);

        if (next_state->is_final) {
          productions[non_terminal].insert(std::string(1, symbol));
        }
      }
    }


  }

  return {productions, *start_state_->id.c_str()};
}


void DFA::Complete() {
  if (alphabet_.empty()) {
    throw std::logic_error("Alphabet is empty. Unable to complete the automaton.");
  }

  states_map_.emplace(dummy_state, std::make_shared<State>(dummy_state, false));

  for (auto &[id, state]: states_map_) {
    for (auto symbol: alphabet_) {
      if (!state->transitions.contains(symbol)) {
        state->transitions[symbol].push_back(states_map_[dummy_state]);
      }
    }
  }
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
