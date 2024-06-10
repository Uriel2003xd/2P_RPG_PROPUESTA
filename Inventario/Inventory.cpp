#include "Inventory.h"
#include <iostream>
#include <algorithm>
#include "../Character/Character.h"



void Inventory::addItem(const Item &item) {
    items.push_back(item);
}

void Inventory::removeItem(const std::string &itemName) {
    items.erase(std::remove_if(items.begin(), items.end(),
                               [&itemName](const Item &item) { return item.getName() == itemName; }),
                items.end());
}

void Inventory::useItem(const std::string &itemName) {
    auto it = std::find_if(items.begin(), items.end(),
                           [&itemName](const Item &item) { return item.getName() == itemName; });

    if (it != items.end()) {
        std::cout << "Usando el articulo: " << it->getName() << std::endl;
        items.erase(it);
    } else {
        std::cout << "Articulo no encontrado en el inventario." << std::endl;
    }
}

void Inventory::listItems() const {
    if (items.empty()) {
        std::cout << "El inventario esta vacio." << std::endl;
    } else {
        std::cout << "\nArticulos en inventario: " << std::endl;
        for (const auto &item : items) {
            std::cout << "- " << item.getName() << ": " << item.getDescription() << std::endl;
        }
    }
}

