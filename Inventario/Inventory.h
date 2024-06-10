#ifndef RPG_INVENTORY_H
#define RPG_INVENTORY_H
#include "Item.h"
#include <vector>
#include <string>



class Inventory {
public:
    void addItem(const Item &item);
    void removeItem(const std::string &itemName);
    void useItem(const std::string &itemName);
    void listItems() const;

private:
    std::vector<Item> items;
};

#endif // RPG_INVENTORY_H
