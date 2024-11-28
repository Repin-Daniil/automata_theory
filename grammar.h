#pragma once
#include <unordered_set>
#include "language.h"

using Productions = std::unordered_map<std::string, std::unordered_set<std::string>>;

struct Grammar {
    Alphabet V_n;
    Alphabet V_t;
    Productions rules;
    char start_symbol;
};

Language GetChains(const Grammar &grammar, std::size_t num_chains) {
    Language language;
    std::queue<std::string> q;
    q.emplace(1, grammar.start_symbol);

    while (!q.empty() && language.size() < num_chains) {
        std::string current = q.front();
        q.pop();

        bool has_left_part = false;

        for (const auto& [left, right] : grammar.rules) {
            size_t pos = current.find(left);

            if (pos != std::string::npos) {
                has_left_part = true;

                for (const auto& replacement : right) {
                    q.push(current.substr(0, pos) + replacement + current.substr(pos + left.size()));
                }

                break;
            }
        }

        if (!has_left_part) {
            language.insert(current);
        }
    }

    return language;
}