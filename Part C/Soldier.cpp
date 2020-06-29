#include "Soldier.h"

using namespace mtm;
using namespace std;

shared_ptr<Character> Soldier::clone() const {
    shared_ptr<Soldier> ptr(new Soldier(*this));
    return ptr;
}

Soldier::Soldier(units_t health, units_t ammo, units_t range, units_t power, Team team): 
    Character(health,ammo,range,power,team) {}

const int Soldier::getMovement() const {
    return movement;
}

void Soldier::attack(Matrix<shared_ptr<Character>>& game_board,const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const{
    shared_ptr<Soldier> attacking_player(game_board(src_coordinates.row, src_coordinates.col));
    if (GridPoint::distance(src_coordinates,dst_coordinates) > attacking_player->getRange()) {
        throw typename mtm::OutOfRange();
    }
    else if (src_coordinates.row != dst_coordinates.row && src_coordinates.col != dst_coordinates.col) { 
        throw typename mtm::OutOfRange();
    }
    else if (attacking_player->getAmmo() == 0) {
        throw typename mtm::OutOfAmmo();
    }
    units_t affected_area = ceil(static_cast<double>(attacking_player->getRange())/3);
    for (int i=0; i<game_board.height(); i++) {
        for (int j=0; j<game_board.width(); j++) {
            GridPoint curr_point(i,j);
            int attack_distance = GridPoint::distance(curr_point, dst_coordinates);
            if(attack_distance <= affected_area) {
                shared_ptr<Character> attacked_player(game_board(curr_point.row, curr_point.col));
                if (attacking_player->getTeam() == attacked_player->getTeam()) {
                    break;
                }
                else if (curr_point == dst_coordinates) {
                    attacked_player->setHealth(-(attacking_player->getPower()));
                }
                else {
                    attacked_player->setHealth(-((attacking_player->getPower()/2)));
                }
                if(attacked_player->getHealth() == 0) {
                    attacked_player = nullptr;
                    game_board(curr_point.row, curr_point.col) = nullptr;
                }
            }
        }
    }
    attacking_player->setAmmo(AMMO_DOWN);
}

void Soldier::reload(Matrix<shared_ptr<Character>>& game_board,const GridPoint& coordinates) {
    shared_ptr<Soldier> curr_player(game_board(coordinates.row, coordinates.col));
    curr_player->setAmmo(ADD_AMMO);
}


         