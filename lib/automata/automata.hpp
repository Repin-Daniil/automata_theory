#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>

#include "language/language.hpp"

static inline std::string dummy_state = "k_fc";

class Automata {
  public:
    Automata(const std::string &start_id, const std::unordered_set<std::string> &states,
             const std::unordered_set<std::string> &final_states,
             const std::unordered_map<std::string, std::unordered_map<char, std::vector<std::string> > > &transitions,
             Alphabet alphabet = {});

    void ToDot(const std::string &filename) const;

    virtual Language GenerateChains(std::size_t max_length) = 0;

    virtual bool Accept(std::string_view chain) = 0;

    [[nodiscard]] Alphabet GetAlphabet() const;
    [[nodiscard]] std::unordered_set<std::string> GetStates() const;
    [[nodiscard]] std::unordered_set<std::string> GetFinalStates() const;
    [[nodiscard]] std::string GetStartState() const;
    [[nodiscard]] std::unordered_map<std::string, std::unordered_map<char, std::vector<std::string> > > GetTransitions() const;

    virtual ~Automata() = default;

    //TODO Генерировать еще запись формального представления
  protected:
    struct State;
    std::unordered_map<std::string, std::shared_ptr<State> > states_map_;
    std::shared_ptr<State> start_state_;
    Alphabet alphabet_;

    struct State {
      std::string id;
      bool is_final = false;
      std::unordered_map<char, std::vector<std::shared_ptr<State> > > transitions = {};
    };
};
