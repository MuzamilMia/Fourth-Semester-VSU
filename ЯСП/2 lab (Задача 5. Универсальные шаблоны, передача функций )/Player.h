#ifndef PLAYER_H
#define PLAYER_H

#include "Weapon.h"

class Player {
private:
    Weapon* bar[SLOTS] = { nullptr, nullptr, nullptr };

public:
    Player();
    ~Player();
    Weapon drop(int pos);
    //void get(Weapon wep);
    Weapon get(Weapon wep);
    void show_hot_bar();
    bool shot(int pos);
    bool is_empty_slots();
};

#endif // PLAYER_H