#ifndef BRUT_INVENTORY_HPP
#define BRUT_INVENTORY_HPP

#include <array>

#include "Player/BrutInventoryItem.hpp"

namespace Brut {

class Inventory {
 public:
  Inventory();
  ~Inventory();

  std::array<InventoryItem, 9> itens = {};
};

}  // namespace Brut

#endif