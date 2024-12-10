#pragma once
#include <iostream>
#include <string>

namespace lab::format {
  inline void PrintHead(std::string title) {
    std::cout << std::endl << "\033[1;34m" << title << "\033[0m" << std::endl;
  }

  inline void PrintTask(std::string problem, std::string solution) {
    std::cout << "\033[1;36m" << problem << "\033[0m = \033[1;32m" << solution <<"\033[0m"<< std::endl;

  }
}