#include "Soldier.h"

using namespace mtm;

std::shared_ptr<Character> Soldier::clone() const {
    std::shared_ptr<Soldier> ptr(new Soldier(*this));
    return ptr;
}

Soldier::Soldier(int health, int ammo, int range, int power): Character(health,ammo,range,power) {}
         