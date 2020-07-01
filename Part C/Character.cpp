#include "Character.h"
#include "Auxiliaries.h"

using namespace mtm;

Character::Character(units_t health,units_t ammo,units_t range,units_t power,Team team, CharacterType type):
    health(health), ammo(ammo), range(range), power(power), team(team), type(type){}

const units_t Character::getHealth(){
    return health;
}

const units_t Character::getAmmo(){
    return ammo;
}

const units_t Character::getRange(){
    return range;
}

const units_t Character::getPower(){
    return power;
}

const Team Character::getTeam(){
    return team;
}

const CharacterType Character::getType(){
    return type;
}

void Character::setHealth(int health_change) {
    this->health = health + health_change;
    if(health < 0){
        health = 0;
    }
}
void Character::setAmmo(int ammo_change) {
    this->ammo = ammo + ammo_change;
    if (ammo < 0) {
        ammo = 0;
    }
}