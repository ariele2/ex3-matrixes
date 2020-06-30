#include "Medic.h"

using namespace mtm;
using namespace std;

shared_ptr<Character> Medic::clone() const {
    shared_ptr<Medic> ptr(new Medic(*this));
    return ptr;
}

Medic::Medic(int health, int ammo, int range, int power,Team team,CharacterType type): 
    Character(health,ammo,range,power,team,type) {}

const int Medic::getMovement() const {
    return movement;
}

void Medic::attack(Matrix<shared_ptr<Character>>& game_board, 
                    const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const {
    shared_ptr<Character> attacking_player = game_board(src_coordinates.row, src_coordinates.col);
    if (GridPoint::distance(src_coordinates,dst_coordinates) > attacking_player->getRange() ) {
        throw typename mtm::OutOfRange();
    }
    else if (attacking_player->getAmmo() == 0) {
        throw typename mtm::OutOfAmmo();
    }
    else if (src_coordinates == dst_coordinates || (game_board(dst_coordinates.row,dst_coordinates.col) == nullptr)){
        throw typename mtm::IllegalTarget();
    }
    shared_ptr<Character> attacked_player = game_board(dst_coordinates.row, dst_coordinates.col);
    if (attacking_player->getTeam() != attacked_player->getTeam()) {
        attacked_player->setHealth(-attacking_player->getPower());
        if(attacked_player->getHealth() == 0) {
            attacked_player = nullptr;
            game_board(dst_coordinates.row, dst_coordinates.col) = nullptr;
        }   
    }
    else {
        attacked_player->setHealth(attacking_player->getPower());
    }
    
    attacking_player->setAmmo(AMMO_DOWN);
}

void Medic::reload(Matrix<shared_ptr<Character>>& game_board,const GridPoint& coordinates) {
    shared_ptr<Character> curr_player = game_board(coordinates.row, coordinates.col);
    curr_player->setAmmo(ADD_AMMO);
}

const units_t Medic::getHealth(){
    return health;
}

const units_t Medic::getAmmo(){
    return ammo;
}

const units_t Medic::getRange(){
    return range;
}

const units_t Medic::getPower(){
    return power;
}

const Team Medic::getTeam(){
    return team;
}

const CharacterType Medic::getType(){
    return type;
}

void Medic::setHealth(int health_change) {
    this->health = health + health_change;
    if(health < 0){
        health = 0;
    }
}
void Medic::setAmmo(int ammo_change) {
    this->ammo = ammo + ammo_change;
    if (ammo < 0) {
        ammo = 0;
    }
}