#ifndef RPG_ITEM_H
#define RPG_ITEM_H

#include <string>

class Item {
public:
    Item(const std::string &name, const std::string &description);

    std::string getName() const;
    std::string getDescription() const;

private:
    std::string name;
    std::string description;
};

#endif // RPG_ITEM_H
