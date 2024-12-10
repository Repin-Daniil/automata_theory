#include <iostream>

#include "grammar/grammar.hpp"

#include "utils/format/formatter.hpp"

int main() {
  using namespace lab::format;
//TODO Сделать вывод грамматики по автомату
  PrintHead("--- №9 ---");

  Grammar grammar({
                    {"S", {"aA"}},
                    {"A", {"bB"}},
                    {"B", {"bB", "c", "cC"}},
                    {"C", {"cC", "c"}},
                  },
                  'S');


  PrintTask("L(G)", GetChains(grammar.GetChains(20)));

  return EXIT_SUCCESS;
}
