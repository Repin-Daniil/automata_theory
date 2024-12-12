#include "nfa.hpp"

NFA::NFA(const std::string &start_id, const std::unordered_set<std::string> &states,
         const std::unordered_set<std::string> &final_states,
         const std::unordered_map<std::string, std::unordered_map<char, std::vector<std::string> > > &
         transitions) : Automata(start_id, states, final_states, transitions) {
}

Language NFA::GenerateChains(std::size_t max_length) {
  Language language;
  std::string current_chain;
  DFS(current_chain, start_state_, language, max_length);
  return language;
}

bool NFA::Accept(std::string_view chain) {
    return DFS(chain, 0, start_state_);
}

bool NFA::DFS(std::string_view chain, std::size_t index, const std::shared_ptr<State> &current_state) {
  if (index == chain.size()) {
    return current_state->is_final;
  }

  char symbol = chain[index];

  // Проверяем переходы по текущему символу
  if (current_state->transitions.contains(symbol)) {
    for (const auto &next_state : current_state->transitions.at(symbol)) {
      if (DFS(chain, index + 1, next_state)) {
        return true;
      }
    }
  }

  // Проверяем ε-переходы (обрабатываем отдельно, не увеличивая index)
  if (current_state->transitions.contains('\0')) {
    for (const auto &next_state : current_state->transitions.at('\0')) {
      if (DFS(chain, index, next_state)) {
        return true;
      }
    }
  }

  return false; // Если ни один путь не оказался верным
}

void NFA::DFS(std::string &current_chain,
              std::shared_ptr<State> current_state,
              Language &language,
              std::size_t max_length) {
  // Если состояние конечное, добавляем цепочку
  if (current_state->is_final) {
    language.insert(current_chain);
  }

  // Прекращаем, если достигли максимальной длины
  if (current_chain.size() >= max_length) {
    return;
  }

  // Рекурсивно обходим все переходы
  for (const auto &[symbol, next_states]: current_state->transitions) {
    for (const auto &next_state: next_states) {
      current_chain.push_back(symbol);
      DFS(current_chain, next_state, language, max_length);
      current_chain.pop_back(); // Отменяем изменения после возвращения
    }
  }
}
