#include "grammar.hpp"

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
      size_t pos = current.find(left);

      if (pos != std::string::npos) {
        has_left_part = true;

        for (const auto &replacement: right) {
          queue.push(current.substr(0, pos) + replacement + current.substr(pos + left.size()));
        }

        break;
      }
    }

    if (!has_left_part) {
      language.insert(current);
    }
  }

  return language;
}
