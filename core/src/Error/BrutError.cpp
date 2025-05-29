#include "Error/BrutError.hpp"

#include <cstdlib>
#include <iostream>

#include <SDL3/SDL.h>

#include "Terminal/TermColor.h"

namespace Brut {

void fatalError(const std::string errorMessage) {
  SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "ERROR: %s\n", errorMessage.c_str());
  std::cerr << TERM_COLOR_RED << "ERROR: " << errorMessage << TERM_COLOR_RESET
            << "\n";
  std::cin.get();
  std::exit(EXIT_FAILURE);
}

}  // namespace Brut
