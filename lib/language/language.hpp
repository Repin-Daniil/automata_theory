#pragma once

#include <set>
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>

using Language = std::set<std::string>;
using Alphabet = std::set<char>;

static inline std::string empty_chain;
static inline std::string inf = "...";
static inline std::string dummy_symbol = "◊";

std::string GetChains(const Language &language);
std::ostream &operator<<(std::ostream &os, const Language &language);

Language Union(const Language &lang1, const Language &lang2);
Language Intersection(const Language &lang1, const Language &lang2);
Language Difference(const Language &lang1, const Language &lang2);

Language Concatenation(const Language &lang1, const Language &lang2);
Language Complement(const Language &language, const Alphabet &alphabet);
Language KleenePlus(const std::set<std::string>& language, int degree);
Language KleeneStar(const std::set<std::string>& language, int degree);


static Alphabet GetAlphabet(const Language &language);
static std::size_t GetMaxLength(const Language &language);
static Language GetVStar(const Alphabet &alphabet, std::size_t max_length);
