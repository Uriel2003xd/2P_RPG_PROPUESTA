#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"
#include "Files/FileHandler.h"

Player* loadPlayerInfo() {
    try {
        char buffer[Player::BUFFER_SIZE];
        FileHandler fileHandler = FileHandler();
        fileHandler.readFromFile("PlayerInfo.data", buffer, Player::BUFFER_SIZE);
        return Player::unserialize(buffer);
    } catch(int error) {
        //Preguntar al usuario el nombre de jugador
        return new Player("Otro Jugador", 7, 15, 7, 8);
    }
}

int main() {
    Player *player = loadPlayerInfo();
    cout << player->getName() << endl;
    cout << player->toString() << endl;
    Enemy *enemy = new Enemy("Carmencita", 15, 6, 2, 5, 10);
    Enemy *enemy2 = new Enemy("Blanquita", 15, 6, 2, 5, 10);

    // Crear algunos ítems
    Item espada("Espada", "Una hoja afilada Que Aumenta Tu Ataque");
    Item pocionMin("Pocion de saludMin", "PocionMin Que Restaura Tu salud.");
    Item pocion("Pocion de salud", "PocionMax Que Restaura Tu salud.");
    Item armadura("Armadura", "Armadura Que Aumenta TU Defensa");

    // Agregar ítems al inventario del jugador
    player->addItemToInventory(espada);
    player->addItemToInventory(pocionMin);
    player->addItemToInventory(pocion);
    player->addItemToInventory(armadura);

    // Mostrar el inventario del jugador
    player->showInventory();

    vector<Character*> participants;

    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    Combat *combat = new Combat(participants);
    combat->doCombat();

    delete player;
    delete enemy;
    delete combat;
    return 0;
}
