#include "automata.hpp"

#include <memory>
#include <fstream>

#include "language/language.hpp"


Automata::Automata(const std::string &start_id, const std::unordered_set<std::string> &states,
                   const std::unordered_set<std::string> &final_states,
                   const std::unordered_map<std::string, std::unordered_map<char, std::vector<std::string> > > &
                   transitions) {
  for (const auto &id: states) {
    states_map_[id] = std::make_shared<State>(State{id, final_states.contains(id)});
  }

  start_state_ = states_map_.at(start_id);

  for (const auto &[from, trans_map]: transitions) {
    for (const auto &[symbol, to_states]: trans_map) {
      for (const auto &to: to_states) {
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
