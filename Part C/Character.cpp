#include "Character.h"
#include "Auxiliaries.h"

using namespace mtm;

Character::Character(units_t health,units_t ammo,units_t range,units_t power,Team team):
    health(health), ammo(ammo), range(range), power(power), team(team){}

const units_t Character::get_health(){
    return health;
}

const units_t Character::get_ammo(){
    return ammo;
}

const units_t Character::get_range(){
    return range;
}

const units_t Character::get_power(){
    return power;
}

const Team Character::get_team(){
    return team;
}

void Character::set_health(int health_change) {
    this->health = health + health_change;
    if(health < 0){
        health = 0;
    }
}
void Character::set_ammo(int ammo_change) {
    this->ammo = ammo + ammo_change;
    if (ammo < 0) {
        ammo = 0;
    }
}
