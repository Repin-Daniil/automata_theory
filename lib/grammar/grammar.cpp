#include "grammar.hpp"
#include <queue>

Grammar::Grammar(Productions rules, char start_symbol) : rules_(std::move(rules)), start_symbol_(start_symbol) {
}

Language Grammar::GetChains(std::size_t num_chains) {
  Language language;
  std::queue<std::string> queue;
  queue.emplace(1, start_symbol_);

  while (!queue.empty() && language.size() < num_chains) {
    std::string current = queue.front();
    queue.pop();

    bool has_left_part = false;

    for (const auto &[left, right]: rules_) {
      size_t pos = 0;

      while ((pos = current.find(left, pos)) != std::string::npos) {
        has_left_part = true;

        for (const auto &replacement: right) {
          std::string new_string = current.substr(0, pos) + replacement + current.substr(pos + left.size());
          queue.push(new_string);
        }

        pos += left.size();
      }
    }

    if (!has_left_part) {
      language.insert(current);
    }
  }

  if (!queue.empty()) {
    language.insert(inf);
  }

  return language;
}

std::tuple<std::set<std::string>, std::set<char>, char, Productions> Grammar::GetFormalRepresentation() const {
  std::set<std::string> non_terminals;
  std::set<char> terminals;

  for (const auto &[lhs, rhs_set]: rules_) {
    non_terminals.insert(lhs);
    for (const auto &rhs: rhs_set) {
      for (char ch: rhs) {
        if (isupper(ch)) {
          non_terminals.insert(std::string(1, ch));
        } else {
          terminals.insert(ch);
        }
      }
    }
  }

  return {non_terminals, terminals, start_symbol_, rules_};
}
