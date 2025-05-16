#include "Player/BrutInventoryItem.hpp"

#include <string>

namespace Brut {

InventoryItem::InventoryItem() : name{"Air"}, id{0} {}

InventoryItem::InventoryItem(std::string _name, unsigned int _id)
    : name{std::move(_name)}, id{_id} {}

InventoryItem::~InventoryItem() {}

}  // namespace Brut