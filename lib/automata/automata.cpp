#include "automata.hpp"

#include <memory>
#include <fstream>
#include <iostream>

#include "language/language.hpp"


Automata::Automata(const std::string &start_id, const std::unordered_set<std::string> &states,
                   const std::unordered_set<std::string> &final_states,
                   const std::unordered_map<std::string, std::unordered_map<char, std::vector<std::string> > > &
                   transitions, Alphabet alphabet) : alphabet_(alphabet) {
  bool alphabet_is_empty = alphabet.empty();

  for (const auto &id: states) {
    states_map_[id] = std::make_shared<State>(id, final_states.contains(id));
  }

  if (!states_map_.contains(start_id)) {
    throw std::invalid_argument("Start state not found in the states set.");
  }

  start_state_ = states_map_.at(start_id);

  for (const auto &[from, trans_map]: transitions) {
    if (!states_map_.contains(from)) {
      throw std::invalid_argument("Transition from a non-existent state: " + from);
    }

    for (const auto &[symbol, to_states]: trans_map) {
      if (!alphabet_is_empty && !alphabet_.contains(symbol)) {
        throw std::invalid_argument("Symbol in transitions is not in the provided alphabet: " + std::string(1, symbol));
      }

      alphabet_.insert(symbol);

      for (const auto &to: to_states) {
        if (!states_map_.contains(to)) {
          throw std::invalid_argument("Transition to a non-existent state: " + to);
        }

        if (states_map_.contains(from) && states_map_.contains(to)) {
          states_map_[from]->transitions[symbol].push_back(states_map_[to]);
        }
      }
    }
  }
}


void Automata::ToDot(const std::string &filename) const {
  std::ofstream dot_file(filename);
  if (!dot_file) {
    throw std::runtime_error("Unable to open file: " + filename);
  }

  dot_file << "digraph finite_state_machine {\n";
  dot_file << "  fontname=\"Times New Roman\";\n";
  dot_file << "  node [fontname=\"Times New Roman\"];\n";
  dot_file << "  edge [fontname=\"Times New Roman\"];\n";
  dot_file << "  rankdir=LR;\n";

  // Конечные состояния — квадраты
  dot_file << "  node [shape = box];\n";
  for (const auto &[id, state]: states_map_) {
    if (state->is_final) {
      dot_file << "  \"" << id << "\";\n";
    }
  }

  // Обычные состояния — круги
  dot_file << "  node [shape = circle];\n";

  // Переходы
  for (const auto &[id, state]: states_map_) {
    for (const auto &[symbol, target_states]: state->transitions) {
      for (const auto &target_state: target_states) {
        dot_file << "  \"" << id << "\" -> \"" << target_state->id
            << "\" [label = \"" << symbol << "\"];\n";
      }
    }
  }

  dot_file << "}\n";
}

[[nodiscard]] Alphabet Automata::GetAlphabet() const {
  return alphabet_;
}

[[nodiscard]] std::unordered_set<std::string> Automata::GetStates() const {
  std::unordered_set<std::string> states;
  for (const auto &[id, state] : states_map_) {
    states.insert(id);
  }
  return states;
}

[[nodiscard]] std::unordered_set<std::string> Automata::GetFinalStates() const {
  std::unordered_set<std::string> final_states;
  for (const auto &[id, state] : states_map_) {
    if (state->is_final) {
      final_states.insert(id);
    }
  }
  return final_states;
}

[[nodiscard]] std::string Automata::GetStartState() const {
  return start_state_ ? start_state_->id : ""; // Проверяем указатель start_state_, возвращаем пустую строку, если он пуст.
}

[[nodiscard]] std::unordered_map<std::string, std::unordered_map<char, std::vector<std::string>>> Automata::GetTransitions() const {
  std::unordered_map<std::string, std::unordered_map<char, std::vector<std::string>>> transitions;

  for (const auto &[id, state] : states_map_) {
    for (const auto &[symbol, next_states] : state->transitions) {
      for (const auto &next_state : next_states) {
        transitions[id][symbol].push_back(next_state->id); // Собираем идентификаторы состояний для переходов.
      }
    }
  }

  return transitions;
}
