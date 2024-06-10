//
// Created by Victor Navarro on 15/02/24.
//
#pragma once
#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H
#include "../Inventario/Inventory.h"
#include "../Character/Character.h"
#include "../Enemy/Enemy.h"
#include "../Combat/Action.h"
#include <vector>
#include <iostream>

class Enemy;


class Player: public Character {

    //TODO: Implement Classes (Mage, Warrior, Rogue, etc..)
    //TODO: Implement Inventory
public:
    void addItemToInventory(const Item &item);
    void removeItemFromInventory(const std::string &itemName);
    void useItemFromInventory(const std::string &itemName);
    void showInventory() const;

private:
    Inventory inventory;
    int level;
    int experience;
    void levelUp();
    void saveProgress();
public:
    Player(char* _name, int _health, int _attack, int _defense, int _speed);
    Player(char* _name, int _health, int _attack, int _defense, int _speed, bool isPlayer, int _level, int _experience);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;
    Character* selectTarget(vector<Enemy*> possibleTargets);
    Action takeAction(vector<Enemy*> enemies);
    char* serialize();
    static Player* unserialize(char* buffer);

    void gainExperience(int exp);
    static const unsigned int BUFFER_SIZE = sizeof (name) + sizeof(health) + sizeof(attack) + sizeof(defense) + sizeof(speed) + sizeof(isPlayer) + sizeof(level) + sizeof(experience);

    //TODO: Implement use object
private:
    char buffer[Player::BUFFER_SIZE];

    void useItemFromInventory(const Item &item);

    void pocion(const Item &item);

    Action handleInventoryAction(vector<Enemy *> vector1);
};


#endif //RPG_PLAYER_H
