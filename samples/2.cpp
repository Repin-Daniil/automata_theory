#include <iostream>

#include "grammar/grammar.hpp"
#include "utils/format/formatter.hpp"

int main() {
  using namespace lab::format;

  PrintHead("--- №2 ---");

  Language language_3 = {"01", "010101"};

  PrintTask("L*",PrintLanguage(KleeneStar(language_3, 2)));
  PrintTask("L+",PrintLanguage(KleenePlus(language_3, 2)));

}
