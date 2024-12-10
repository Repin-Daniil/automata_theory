#include <iostream>

#include "automata/dfa.hpp"
#include "grammar/grammar.hpp"

#include "utils/format/formatter.hpp"

int main() {
  using namespace lab::format;

  std::unordered_set<std::string> states = {"S", "A", "B", "C"};
  std::unordered_set<std::string> final_states = {"C"};
  std::unordered_map<std::string, std::unordered_map<char, std::string> > transitions = {
    {"S", {{'a', "A"}}},
    {"A", {{'b', "B"}}},
    {"B", {{'b', "B"}, {'c', "C"}}},
    {"C", {{'c', "C"}}}
  };

  // Создаем DFA
  DFA dfa("S", states, final_states, transitions);

  // Генерация цепочек длиной до 5
  auto chains = dfa.GenerateChains(5);
  std::cout << "Generated chains:" << std::endl;
  for (const auto &chain: chains) {
    std::cout << chain << std::endl;
  }

  // Проверка цепочек
  std::cout << "Is 'ab' valid? " << (dfa.IsValidChain("ab") ? "Yes" : "No") << std::endl;
  std::cout << "Is 'abc' valid? " << (dfa.IsValidChain("abc") ? "Yes" : "No") << std::endl;


  return EXIT_SUCCESS;
}
