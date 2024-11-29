#include <iostream>

#include "language/language.hpp"
#include "grammar/grammar.hpp"

void SolveTask1() {
  std::cout << "\033[1;34m--- №1 ---\033[0m" << std::endl; // Зеленый цвет
  Alphabet alphabet = {'a', 'b'};
  Language language_1 = {"a", "aa", "baa"};
  Language language_2 = {"b", "aa", "abb"};

  std::cout << "\033[1;36mL1 ∪ L2 \033[0m= \033[1;32m" << Union(language_1, language_2) << std::endl;
  std::cout << "\033[1;36mL1 ∩ L2 \033[0m= \033[1;32m" << Intersection(language_1, language_2) << std::endl;

  std::cout << "\033[1;36mL1 \\ L2 \033[0m= \033[1;32m" << Difference(language_1, language_2) << std::endl;
  std::cout << "\033[1;36mL2 \\ L1 \033[0m= \033[1;32m" << Difference(language_2, language_1) << std::endl;

  std::cout << "\033[1;36mL1L2 \033[0m= \033[1;32m" << Concatenation(language_1, language_2) << std::endl;
  std::cout << "\033[1;36mL2L1 \033[0m= \033[1;32m" << Concatenation(language_2, language_1) << std::endl;

  std::cout << "\033[1;36mL1' \033[0m= \033[1;32m" << Complement(language_1, alphabet) << std::endl;
  std::cout << "\033[1;36mL2' \033[0m= \033[1;32m" << Complement(language_2, alphabet) << std::endl;
}

void SolveTask2() {
  std::cout << std::endl << "\033[1;34m--- №2 ---\033[0m" << std::endl;
  Language language_3 = {"01", "010101"};

  std::cout << "\033[1;36mL* \033[0m= \033[1;32m" << KleeneStar(language_3, 2) << std::endl;
  std::cout << "\033[1;36mL+ \033[0m= \033[1;32m" << KleenePlus(language_3, 2) << std::endl;
}

void SolveTask3() {
  std::cout << std::endl << "\033[1;34m--- №3 ---\033[0m" << std::endl;

  Grammar grammar({
                    {"S", {"abcA"}},
                    {"A", {"bbbS", ""}}
                  },
                  'S');

  std::cout << "\033[1;36mL(G) \033[0m= \033[1;32m" << grammar.GetChains(10) << std::endl;
}

void SolveTask4() {
  std::cout << std::endl << "\033[1;34m--- №4 ---\033[0m" << std::endl;

  Grammar grammar_4(
    {
      {"S", {"", "A", "B"}},
      {"A", {"0A", "0"}},
      {"B", {"1B", "1"}}
    },
    'S');

  std::cout << "\033[1;36mL(G) \033[0m= \033[1;32m" << grammar_4.GetChains(20) << std::endl;
}

int main() {
  SolveTask1();
  SolveTask2();
  SolveTask3();
  SolveTask4();

  return EXIT_SUCCESS;
}
