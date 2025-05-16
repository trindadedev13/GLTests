#include "Error/BrutError.hpp"

#include <cstdlib>
#include <iostream>

#include "Terminal/TermColor.h"

namespace Brut {

void fatalError(const std::string errorMessage) {
  std::cerr << TERM_COLOR_RED << "ERROR: " << errorMessage << TERM_COLOR_RESET
            << "\n";
  std::cin.get();
  exit(EXIT_FAILURE);
}

}  // namespace Brut