#include <iostream>

#include "automata/nfa/nfa.hpp"
#include "grammar/grammar.hpp"

#include "utils/format/formatter.hpp"

//TODO Можно сделать функцию возвращающая все эти сеты, чтобы самим не писать тип, а поставить авто
int main() {
  using namespace lab::format;
  using namespace std::literals;

  PrintHead("--- №6 ---");

  std::unordered_set states = {"k1"s, "k2"s, "k3"s};
  std::unordered_set final_states = {"k3"s};
  std::unordered_map<std::string, std::unordered_map<char, std::vector<std::string>>> transitions = {
    {"k1", {{'x', {"k1", "k2", "k3"}}, {'0', {}}}},
    {"k2", {{'x', {}}, {'0', {"k2", "k3"}}}},
    {"k3", {{'x', {"k3"}}, {'0', {}}}}
  };

  NFA nfa("k1", states, final_states, transitions);

  auto chains = nfa.GenerateChains(5);
  PrintTask("L(M)", GetChains(chains));

  nfa.ToDot("nfa.dot");
  PrintTask("Графическое представление: ", "nfa.dot");

  return EXIT_SUCCESS;
}
