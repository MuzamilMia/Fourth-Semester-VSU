#include "Player.h"
#include <iostream>

Player::Player() {}

Player::~Player() {
    for (size_t i = 0; i < SLOTS; i++) {
        delete bar[i];
        bar[i] = nullptr;
    }
}

//Weapon Player::drop(int pos) {
//    if (pos < 0 || pos >= SLOTS || !bar[pos]) {
//        return Weapon();
//    }
//    Weapon res = *(bar[pos]);
//    delete bar[pos];
//    bar[pos] = nullptr;
//    return res;
//}
Weapon Player::drop(int pos) {
    if (pos < 0 || pos >= SLOTS) {
        std::cout << "Invalid slot index: " << pos << "\n";
        return Weapon();
    }
    if (!bar[pos]) {
        std::cout << "Slot " << pos + 1 << " is null\n";
        return Weapon();
    }
    Weapon res = *(bar[pos]);
    std::cout << "Dropping weapon: " << res.name << " from slot " << pos + 1 << "\n";
    delete bar[pos];
    bar[pos] = nullptr;
    return res;
}

//void Player::get(Weapon wep) {
//    if (wep.slot < 1 || wep.slot > SLOTS) {
//        throw std::invalid_argument("Invalid slot number");
//    }
//    if (bar[wep.slot - 1]) {
//        delete bar[wep.slot - 1];
//    }
//    bar[wep.slot - 1] = new Weapon(wep);
//}

Weapon Player::get(Weapon wep) {
    if (wep.slot < 1 || wep.slot > SLOTS) {
        throw std::invalid_argument("Invalid slot number");
    }
    Weapon replaced; 

    if (bar[wep.slot - 1]) {
        replaced = *(bar[wep.slot - 1]); 
        delete bar[wep.slot - 1]; 
    }
    bar[wep.slot - 1] = new Weapon(wep); 
    return replaced; 
}

void Player::show_hot_bar() {
    for (size_t i = 0; i < SLOTS; i++) {
        std::cout << "--------------\n";
        if (bar[i]) {
            std::cout << *bar[i];
        }
        else {
            std::cout << "Slot " << i + 1 << " empty\n";
        }
        std::cout << "--------------\n";
    }
}

bool Player::shot(int pos) {
    return pos >= 0 && pos < SLOTS && bar[pos] && bar[pos]->shot();
}

bool Player::is_empty_slots() {
    for (size_t i = 0; i < SLOTS; i++) {
        if (bar[i]) {
            return false;
        }
    }
    return true;
}