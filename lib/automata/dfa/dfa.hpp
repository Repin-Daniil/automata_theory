#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "automata/automata.hpp"
#include "grammar/grammar.hpp"
#include "language/language.hpp"


class DFA final : public Automata {
  public:
    DFA(const std::string &start_id,
        const std::unordered_set<std::string> &states,
        const std::unordered_set<std::string> &final_states,
        const std::unordered_map<std::string, std::unordered_map<char, std::string> > &transitions, Alphabet alphabet = {});

    bool Accept(std::string_view chain) override;
    Language GenerateChains(std::size_t max_length) override; //FIXME Можно же конст сделать многое
    Grammar GetRegularGrammar();
    void Complete();

  //TODO минимизация
  //TODO получение связного

  private:
    static std::unordered_map<std::string, std::unordered_map<char, std::vector<std::string> > > TransformTransitions(
      const std::unordered_map<std::string, std::unordered_map<char, std::string> > &transitions);
};

// Дополнить до полного с k_fc k фиктивный
//   // Построить регулярную грамматику
