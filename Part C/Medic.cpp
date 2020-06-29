#include "Medic.h"

using namespace mtm;
using namespace std;

shared_ptr<Character> Medic::clone() const {
    shared_ptr<Medic> ptr(new Medic(*this));
    return ptr;
}

Medic::Medic(int health, int ammo, int range, int power,Team team): 
    Character(health,ammo,range,power,team) {}

const int Medic::getMovement() const {
    return movement;
}

void Medic::attack(Game& game,const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const {
    shared_ptr<Medic> attacking_player(game.board(src_coordinates.row, src_coordinates.col));
    if (GridPoint::distance(src_coordinates,dst_coordinates) > attacking_player->getRange() ) {
        throw typename mtm::OutOfRange();
    }
    else if (attacking_player->getAmmo() == 0) {
        throw typename mtm::OutOfAmmo();
    }
    else if (src_coordinates == dst_coordinates || (game.board(dst_coordinates.row,dst_coordinates.col) == nullptr)){
        throw typename mtm::IllegalTarget();
    }
    shared_ptr<Medic> attacking_player(game.board(src_coordinates.row, src_coordinates.col));
    shared_ptr<Character> attacked_player(game.board(dst_coordinates.row, dst_coordinates.col));
    if (attacking_player->getTeam() != attacked_player->getTeam()) {
        attacked_player->setHealth(-attacking_player->getPower());
        if(attacked_player->getHealth() == 0) {
            attacked_player = nullptr;
            game.board(dst_coordinates.row, dst_coordinates.col) = nullptr;
        }   
    }
    else {
        attacked_player->setHealth(attacking_player->getPower());
    }
    
    attacking_player->setAmmo(AMMO_DOWN);
}

void Medic::reload(Game& game,const GridPoint& coordinates) {
    //exceptions
    shared_ptr<Medic> curr_player(game.board(coordinates.row, coordinates.col));
    curr_player->setAmmo(ADD_AMMO);
}