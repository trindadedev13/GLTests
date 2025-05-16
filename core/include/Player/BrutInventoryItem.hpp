#ifndef BRUT_INVENTORY_ITEM_HPP
#define BRUT_INVENTORY_ITEM_HPP

#include <string>

namespace Brut {

class InventoryItem {
 public:
  InventoryItem();
  InventoryItem(std::string name, unsigned int id);
  ~InventoryItem();
  unsigned int id;
  std::string name;
};

}  // namespace Brut

#endif