#include <iostream>

// #include "language.h"
#include "grammar.h"

int main() {
    std::cout << "--- №1 ---" << std::endl;
    Alphabet alphabet = {'a', 'b'};
    Language language_1 = {"a", "aa", "baa"};
    Language language_2 = {"b", "aa", "abb"};


    std::cout << "Объединение = " << Union(language_1, language_2) << std::endl;
    std::cout << "Пересечение = " << Intersection(language_1, language_2) << std::endl;

    std::cout << "L1 \\ L2 = " << Difference(language_1, language_2) << std::endl;
    std::cout << "L1 \\ L2 = " << Difference(language_2, language_1) << std::endl;

    std::cout << "L1L2 = " << Concatenation(language_2, language_1) << std::endl;
    std::cout << "L2L1 = " << Concatenation(language_2, language_1) << std::endl;


    std::cout << "Дополнение L1 = " << Complement(language_1, alphabet) << std::endl;
    std::cout << "Дополнение L2 = " << Complement(language_2, alphabet) << std::endl;


    std::cout << std::endl << "--- №2 ---" << std::endl;
    Language language_3 = {"01", "010101"};

    std::cout << "L* = " << KleeneStar(language_3, 2) << std::endl;
    std::cout << "L+ = " << KleenePlus(language_3, 2) << std::endl;


    std::cout << std::endl << "--- №3 ---" << std::endl;

    Grammar grammar = {
        {'S', 'A'},
        {'a', 'b', 'c'},
        {{"S", {"abcA"}}, {"A", {"bbbS", ""}}},
        'S'
    };

    std::cout << GetChains(grammar, 3) << std::endl;


    std::cout << std::endl << "--- №4 ---" << std::endl;

    Productions rules_4{
        {"S", {"", "A", "B"}},
        {"A", {"0A", "0"}},
        {"B", {"1B", "1"}}
    };

    Grammar grammar_4 = {
        {'S', 'A', 'B'},
        {'0', '1'},
        rules_4,
        'S'
    };

    std::cout << GetChains(grammar_4, 10) << std::endl;

    return EXIT_SUCCESS;
}
