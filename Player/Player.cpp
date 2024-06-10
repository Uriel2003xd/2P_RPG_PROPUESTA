//
// Created by Victor Navarro on 15/02/24.
//

#include "Player.h"
#include <iostream>
#include "../Files/FileHandler.h"
#include "../Character/Character.h"
#include "../Inventario/inventory.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../Combat/Combat.h"
#include "../Files/FileHandler.h"
using namespace std;

void Player::addItemToInventory(const Item &item) {
    inventory.addItem(item);
}


void Player::removeItemFromInventory(const std::string &itemName) {
    inventory.removeItem(itemName);
}


void Player::useItemFromInventory(const std::string &itemName) {
    inventory.useItem(itemName);
}


void Player::showInventory() const {
    inventory.listItems();
}
void Player::saveProgress() {
    char* buffer = this->serialize();
    FileHandler fileHandler = FileHandler();

    fileHandler.writeToFile("PlayerInfo.data", buffer, Player::BUFFER_SIZE);
}

Player::Player(char* _name, int _health, int _attack, int _defense, int _speed) : Character(_name, _health, _attack, _defense, _speed, true) {
    level = 1;
    experience = 0;
}

Player::Player(char* _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer, int _level, int _experience) : Character(_name, _health, _attack, _defense, _speed, _isPlayer) {
    level = _level;
    experience = _experience;
}


void Player::doAttack(Character *target) {
    target->takeDamage(attack);
}

void Player::takeDamage(int damage) {
    int trueDamage = damage - defense;

    health-= trueDamage;

    cout << name << " Recibio " << trueDamage << " De Ataque!" << endl;

    if(health <= 0) {
        cout << name << " Ha Sido Derrotado!" << endl;
    }
}

void Player::levelUp() {
    level++;
}

void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        levelUp();
        experience = 100-experience;
    }
}

Character* Player::selectTarget(vector<Enemy*> possibleTargets) {
    int selectedTarget = 0;
    cout << "Selecciona al enemigo que vas atacar: " << endl;
    for (int i = 0; i < possibleTargets.size(); i++) {
        cout << i << ". " << possibleTargets[i]->getName() << endl;
    }

    //TODO: Add input validation
    cin >> selectedTarget;
    return possibleTargets[selectedTarget];
}


Action Player::takeAction(vector<Enemy*> enemies) {
    int action = 0;
    cout << getName() << "\nSigue el turno de: " << endl
         << "1. Atacar" << endl
         << "2. Inventario\n"
         << "3. Guardar Progreso" << endl;

    // TODO: Validate input
    cin >> action;
    Action currentAction;
    Character* target = nullptr;

    switch(action) {
        case 1:
            target = selectTarget(enemies);
            currentAction.target = target;
            currentAction.action = [this, target](){
                doAttack(target);
            };
            currentAction.speed = getSpeed();
            break;
        case 2:
            return handleInventoryAction(enemies);
        case 3:
            saveProgress();
            return takeAction(enemies);
        default:
            cout << "Accion no valida(1-3)" << endl;
            return takeAction(enemies);
    }

    return currentAction;
}

Action Player::handleInventoryAction(vector<Enemy*> enemies) {
    int inventarioo = 0;
    cout << getName() << "\nInventario: " << endl
         << "1. Hoja afilada   | +5 de Ataque" << endl
         << "2. Pocion de salud| +20 De Vida\n"
         << "3. Pocion de Salud| +50 De Vida\n"
         << "4. Armadura Debil | +3 De Defensa" << endl;

    // TODO: Validate input
    cin >> inventarioo;

    switch(inventarioo) {
        case 1:
            useItemFromInventory("Espada");
            attack += 5;
            cout << "Has usado Hoja Afilada. Aumento actual de ataque: " << attack << "\n";
            removeItemFromInventory("Espada");
            showInventory();
            break;
        case 2:
            useItemFromInventory("Pocion de saludMin");
            health += 20;
            cout << "Has usado una pocionMin de salud. Vida actual: " << health << "\n";
            removeItemFromInventory("Pocion de saludMin");
            showInventory();
            return takeAction(enemies);
        case 3:
            useItemFromInventory("Pocion de salud");
            health += 50;
            cout << "Has usado una pocionMax de salud. Vida actual: " << health << "\n";
            removeItemFromInventory("Pocion de salud");
            showInventory();
            return takeAction(enemies);
        case 4:
            useItemFromInventory("Armadura");
            defense += 3;
            cout << "Has usado una Armadura. Armadura actual: " << defense << "\n";
            removeItemFromInventory("Armadura");
            showInventory();
            return takeAction(enemies);
        default:
            cout << "Accion no valida(1-4)" << endl;
            return takeAction(enemies);
    }

    Action dummyAction;
    return dummyAction;  // This line is just to return something in all code paths.
}

char* Player::serialize() {
    char* iterator = buffer;

    memcpy(iterator, &name, sizeof(name));
    iterator += sizeof(name);

    memcpy(iterator, &health, sizeof(health));
    iterator += sizeof(health);

    memcpy(iterator, &attack, sizeof(attack));
    iterator += sizeof(attack);

    memcpy(iterator, &defense, sizeof(defense));
    iterator += sizeof(defense);

    memcpy(iterator, &speed, sizeof(speed));
    iterator += sizeof(speed);

    memcpy(iterator, &isPlayer, sizeof(isPlayer));
    iterator += sizeof(isPlayer);

    memcpy(iterator, &level, sizeof(level));
    iterator += sizeof(level);

    memcpy(iterator, &experience, sizeof(experience));

    return buffer;
}

Player* Player::unserialize(char* buffer) {
    char* iterator = buffer;
    char name[30];
    int health, attack, defense, speed, level, experience;
    bool isPlayer;

    memcpy(&name, iterator, sizeof(name));
    iterator += sizeof(name);

    memcpy(&health, iterator, sizeof(health));
    iterator += sizeof(health);

    memcpy(&attack, iterator, sizeof(attack));
    iterator += sizeof(attack);

    memcpy(&defense, iterator, sizeof(defense));
    iterator += sizeof(defense);

    memcpy(&speed, iterator, sizeof(speed));
    iterator += sizeof(speed);

    memcpy(&isPlayer, iterator, sizeof(isPlayer));
    iterator += sizeof(isPlayer);

    memcpy(&level, iterator, sizeof(level));
    iterator += sizeof(level);

    memcpy(&experience, iterator, sizeof(experience));
    iterator += sizeof(experience);

    return new Player(name, health, attack, defense, speed, isPlayer, level, experience);
}