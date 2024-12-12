#pragma once
#include "automata/automata.hpp"

class NFA : public Automata {
  public:
    NFA(const std::string &start_id,
        const std::unordered_set<std::string> &states,
        const std::unordered_set<std::string> &final_states,
        const std::unordered_map<std::string, std::unordered_map<char, std::vector<std::string> > > &
        transitions);

    Language GenerateChains(std::size_t max_length) override;

    bool Accept(std::string_view chain) override;

  private:
    void DFS(std::string &current_chain, std::shared_ptr<State> current_state, Language &language, std::size_t max_len);
    bool DFS(std::string_view chain, std::size_t index, const std::shared_ptr<State> &current_state);
};
