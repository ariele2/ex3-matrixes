#ifndef HW3_MEDIC_C
#define HW3_MEDIC_C
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
        attacking_player->setAmmo(AMMO_DOWN);
        if(attacked_player->getHealth() == 0) {
            attacked_player = nullptr;
            game_board(dst_coordinates.row, dst_coordinates.col) = nullptr;
        }   
    }
    else {
        attacked_player->setHealth(attacking_player->getPower());
    }
}

void Medic::reload(Matrix<shared_ptr<Character>>& game_board,const GridPoint& coordinates) {
    shared_ptr<Character> curr_player = game_board(coordinates.row, coordinates.col);
    curr_player->setAmmo(ADD_AMMO);
}


#endif