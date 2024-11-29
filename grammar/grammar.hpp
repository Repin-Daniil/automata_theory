#pragma once

#include <unordered_set>

#include "language/language.hpp"

using Productions = std::unordered_map<std::string, std::unordered_set<std::string> >;

class Grammar {
  public:
    Grammar(Productions rules, char start_symbol);
    Language GetChains(std::size_t num_chains);

  private:
    Productions rules_;
    char start_symbol_;

    // Alphabet Vn;
    // Alphabet Vt;
};
