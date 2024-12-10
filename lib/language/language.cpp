#include "language.hpp"


struct OutputComparator {
  bool operator()(const std::string& a, const std::string& b) const {
    if (a.size() != b.size()) {
      return a.size() < b.size();
    }

    return a < b;
  }
};

inline std::string PrintLanguage(const Language &language) {
    std::stringstream result;
    std::string delimiter = ", ";
    bool is_inf = false;

    auto chains = std::vector(language.begin(), language.end());
    std::ranges::sort(chains, OutputComparator());

    for (std::string_view chain : chains) {
        if (chain == inf) {
            is_inf = true;
            continue;
        }

        result << (chain.empty() ? "人" : chain) << delimiter;
    }

    auto str = result.str();

    if(is_inf) {
        str += inf;
    } else if(str.size() >= delimiter.size() + 1){
        str.erase(str.size() - delimiter.size());
    }

    return "{" + str + "}";
}

std::ostream &operator<<(std::ostream &os, const Language &language) {
  os << PrintLanguage(language);

  return os;
}


Language Union(const Language &lang1, const Language &lang2) {
    Language result;
    std::set_union(lang1.begin(), lang1.end(), lang2.begin(), lang2.end(), std::inserter(result, result.begin()));
    return result;
}

Language Intersection(const Language &lang1, const Language &lang2) {
    Language result;
    std::set_intersection(lang1.begin(), lang1.end(), lang2.begin(), lang2.end(),
                          std::inserter(result, result.begin()));
    return result;
}

Language Difference(const Language &lang1, const Language &lang2) {
    Language result;
    std::set_difference(lang1.begin(), lang1.end(), lang2.begin(), lang2.end(), std::inserter(result, result.begin()));
    return result;
}

Language Concatenation(const Language &lang1, const Language &lang2) {
    Language result;

    for (const auto &str1: lang1) {
        for (const auto &str2: lang2) {
            result.insert(str1 + str2);
        }
    }

    return result;
}

Alphabet GetAlphabet(const Language &language) {
    Alphabet alphabet;

    for (const auto &word: language) {
        alphabet.insert(word.begin(), word.end());
    }

    return alphabet;
}

std::size_t GetMaxLength(const Language &language) {
    std::size_t max_length = 0;

    for (std::string_view word: language) {
        max_length = std::max(max_length, word.length());
    }

    return max_length;
}

Language GetVStar(const Alphabet &alphabet, std::size_t max_length) {
    Language result;
    result.insert(empty_chain);

    for (std::size_t len = 1; len <= max_length; ++len) {
        Language temp;

        for (const auto &prefix: result) {
            for (char symbol: alphabet) {
                if (prefix.size() < len) {
                    temp.insert(prefix + symbol);
                }
            }
        }

        result.insert(temp.begin(), temp.end());
    }

    result.insert(inf);
    return result;
}

Language Complement(const Language &language, const Alphabet &alphabet) {
    std::size_t max_length = GetMaxLength(language);
    Language v_star = GetVStar(alphabet, max_length + 1);

    return Difference(v_star, language);
}


Language KleeneStar(const std::set<std::string>& language, int degree) {
    Language result;
    result.insert(empty_chain);

    auto current = language;

    for(std::size_t len = 1; len <= degree; ++len) {
        result.insert(current.begin(), current.end());
        current = Concatenation(current, language);
    }

    result.insert(inf);

    return result;
}

Language KleenePlus(const std::set<std::string>& language, int degree) {
    auto result = KleeneStar(language, degree);
    result.erase(empty_chain);

    return result;
}

