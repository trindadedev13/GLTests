#include "Error/BrutError.hpp"

#include <cstdlib>
#include <iostream>

namespace Brut {
void fatalError(const std::string errorMessage) {
  std::cout << "ERROR: " << errorMessage << "\n";
  std::cin.get();
  exit(EXIT_FAILURE);
}
}  // namespace Brut