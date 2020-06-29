#include "Medic.h"

using namespace mtm;
using namespace std;

shared_ptr<Character> Medic::clone() const {
    shared_ptr<Medic> ptr(new Medic(*this));
    return ptr;
}

Medic::Medic(int health, int ammo, int range, int power,Team team): 
    Character(health,ammo,range,power,team) {}

const int Medic::move() const {
    return movement;
}

void Medic::attack(Game& game,const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const {
    //exceptions
    shared_ptr<Medic> attacking_player(game.board(src_coordinates.row, src_coordinates.col));
    shared_ptr<Character> attacked_player(game.board(dst_coordinates.row, dst_coordinates.col));
    if (attacking_player->get_team() != attacked_player->get_team()) {
        attacked_player->set_health(-attacking_player->get_power());
        if(attacked_player->get_health() == 0) {
            attacked_player = nullptr;
            game.board(dst_coordinates.row, dst_coordinates.col) = nullptr;
        }   
    }
    else {
        attacked_player->set_health(attacking_player->get_power());
    }
    
    attacking_player->set_ammo(AMMO_DOWN);
}

void Medic::reload(Game& game,const GridPoint& coordinates) {
    //exceptions
    shared_ptr<Medic> curr_player(game.board(coordinates.row, coordinates.col));
    curr_player->set_ammo(ADD_AMMO);
}