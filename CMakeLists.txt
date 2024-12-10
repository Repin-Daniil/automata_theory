cmake_minimum_required(VERSION 3.22)
project(automata_theory)

set(CMAKE_CXX_STANDARD 20)

add_library(AutomataLib STATIC
        lib/language/language.hpp lib/language/language.cpp
        lib/grammar/grammar.hpp lib/grammar/grammar.cpp
        lib/utils/format/formatter.hpp
        lib/automata/dfa.cpp
        lib/automata/dfa.hpp)

add_executable(task_1 samples/1.cpp)
add_executable(task_2 samples/2.cpp)
add_executable(task_3 samples/3.cpp)
add_executable(task_4 samples/4.cpp)
add_executable(task_5 samples/5.cpp)
add_executable(task_6 samples/6.cpp)
add_executable(task_7 samples/7.cpp)
add_executable(task_8 samples/8.cpp)
add_executable(task_9 samples/9.cpp)
add_executable(task_10 samples/10.cpp)
add_executable(task_11 samples/11.cpp)
add_executable(task_12 samples/12.cpp)

target_link_libraries(task_1 PRIVATE AutomataLib)
target_link_libraries(task_2 PRIVATE AutomataLib)
target_link_libraries(task_3 PRIVATE AutomataLib)
target_link_libraries(task_4 PRIVATE AutomataLib)
target_link_libraries(task_5 PRIVATE AutomataLib)
target_link_libraries(task_6 PRIVATE AutomataLib)
target_link_libraries(task_7 PRIVATE AutomataLib)
target_link_libraries(task_8 PRIVATE AutomataLib)
target_link_libraries(task_9 PRIVATE AutomataLib)
target_link_libraries(task_10 PRIVATE AutomataLib)
target_link_libraries(task_11 PRIVATE AutomataLib)
target_link_libraries(task_12 PRIVATE AutomataLib)

include_directories(lib/)