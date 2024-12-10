#pragma once
#include <unordered_set>
//
// #include "language/language.hpp"
//
// struct State {
//   std::string symbol;
//   bool is_final;
//   std::unordered_map<> transitions;
// };
//
// using Language = std::set<std::string>;
//
// class DFA {
//   public:
//   Language GetChains();
//     // Дополнить до полного с k_fc k фиктивный
//   // Построить регулярную грамматику
//   private:
//   start_;
//   std::unordered_set  states_;
//   std::unordered_set finite_states_;
//   std::unordered_map transitions_;
// };

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <memory>

class DFA {
public:
    // Определение состояния
    struct State {
        std::string id;
        bool is_final;
        std::unordered_map<char, std::shared_ptr<State>> transitions;

        State(const std::string& id, bool is_final = false)
            : id(id), is_final(is_final) {}
    };

    // Конструктор
    DFA(const std::string& start_id,
        const std::unordered_set<std::string>& states,
        const std::unordered_set<std::string>& final_states,
        const std::unordered_map<std::string, std::unordered_map<char, std::string>>& transitions) {
        // Создаем состояния
        for (const auto& id : states) {
            auto is_final = final_states.find(id) != final_states.end();
            state_map_[id] = std::make_shared<State>(id, is_final);
        }

        // Устанавливаем начальное состояние
        start_ = state_map_.at(start_id);

        // Добавляем переходы
        for (const auto& [from, trans_map] : transitions) {
            for (const auto& [symbol, to] : trans_map) {
                if (state_map_.count(from) && state_map_.count(to)) {
                    state_map_[from]->transitions[symbol] = state_map_[to];
                }
            }
        }
    }

    // Генерация цепочек в порядке возрастания длины
    std::unordered_set<std::string> GenerateChains(size_t max_length) {
        std::unordered_set<std::string> chains;
        std::queue<std::pair<std::string, std::shared_ptr<State>>> queue;

        queue.emplace("", start_);
        while (!queue.empty()) {
            auto [current_chain, current_state] = queue.front();
            queue.pop();

            if (current_state->is_final) {
                chains.insert(current_chain);
            }

            if (current_chain.size() < max_length) {
                for (const auto& [symbol, next_state] : current_state->transitions) {
                    queue.emplace(current_chain + symbol, next_state);
                }
            }
        }

        return chains;
    }

    // Проверка, является ли цепочка допустимой
    bool IsValidChain(const std::string& chain) {
        return DFS(chain, 0, start_);
    }

private:
    std::shared_ptr<State> start_;
    std::unordered_map<std::string, std::shared_ptr<State>> state_map_;

    bool DFS(const std::string& chain, size_t index, const std::shared_ptr<State>& current_state) {
        if (index == chain.size()) {
            return current_state->is_final;
        }

        char symbol = chain[index];
        if (current_state->transitions.find(symbol) == current_state->transitions.end()) {
            return false;
        }

        return DFS(chain, index + 1, current_state->transitions[symbol]);
    }
};
