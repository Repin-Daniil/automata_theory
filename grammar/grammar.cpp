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

    for (const auto &[left, right] : rules_) {
      size_t pos = 0;

      while ((pos = current.find(left, pos)) != std::string::npos) {
        has_left_part = true;

        for (const auto &replacement : right) {
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

  return language;
}
