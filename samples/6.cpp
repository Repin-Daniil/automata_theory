#include <iostream>

#include "automata/NFA/nfa.hpp"
#include "grammar/grammar.hpp"

#include "utils/format/formatter.hpp"

int main() {
  using namespace lab::format;

  std::unordered_set<std::string> states = {"k1", "k2", "k3"};
  std::unordered_set<std::string> final_states = {"k3"};
  std::unordered_map<std::string, std::unordered_map<char, std::vector<std::string>>> transitions = {
    {"k1", {{'x', {"k1", "k2", "k3"}}, {'0', {}}}},
    {"k2", {{'x', {}}, {'0', {"k2", "k3"}}}},
    {"k3", {{'x', {"k3"}}, {'0', {}}}}
  };

  NFA nfa("k1", states, final_states, transitions);

  auto chains = nfa.GenerateChains(5);
  std::cout << "L(M) = " << chains << std::endl;

  nfa.ToDot("nfa.dot");

  return 0;

  return EXIT_SUCCESS;
}
