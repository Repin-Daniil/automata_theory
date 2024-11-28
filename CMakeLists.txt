cmake_minimum_required(VERSION 3.29)
project(automata_theory)

set(CMAKE_CXX_STANDARD 20)

add_executable(automata_theory main.cpp language.h  grammar.h)
