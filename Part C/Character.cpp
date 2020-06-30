#include "Character.h"
#include "Auxiliaries.h"

using namespace mtm;

Character::Character(units_t health,units_t ammo,units_t range,units_t power,Team team,CharacterType type):
    health(health), ammo(ammo), range(range), power(power), team(team),type(type){}

