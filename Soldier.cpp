#include "Soldier.h"

using namespace mtm;
using namespace std;

shared_ptr<Character> Soldier::clone() const {
    shared_ptr<Soldier> ptr(new Soldier(*this));
    return ptr;
}

Soldier::Soldier(units_t health, units_t ammo, units_t range, units_t power, Team team): 
    Character(health,ammo,range,power,team) {}

const int Soldier::move() const {
    return movement;
}

void Soldier::attack(Game& game,const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const{
    //exceptions
    shared_ptr<Soldier> attacking_player(game.board(src_coordinates.row, src_coordinates.col));
    units_t affected_area = ceil(static_cast<double>(attacking_player->get_range())/3);
    for (int i=0; i<game.height; i++) {
        for (int j=0; j<game.width; j++) {
            GridPoint curr_point(i,j);
            int attack_distance = GridPoint::distance(curr_point, dst_coordinates);
            if(attack_distance <= affected_area) {
                shared_ptr<Character> attacked_player(game.board(curr_point.row, curr_point.col));
                if (attacking_player->get_team() == attacked_player->get_team()) {
                    break;
                }
                else if (curr_point == dst_coordinates) {
                    attacked_player->set_health(-(attacking_player->get_power()));
                }
                else {
                    attacked_player->set_health(-((attacking_player->get_power()/2)));
                }
                if(attacked_player->get_health() == 0) {
                    attacked_player = nullptr;
                    game.board(curr_point.row, curr_point.col) = nullptr;
                }
            }
        }
    }
    attacking_player->set_ammo(AMMO_DOWN);
}

void Soldier::reload(Game& game,const GridPoint& coordinates) {
    //exceptions
    shared_ptr<Soldier> curr_player(game.board(coordinates.row, coordinates.col));
    curr_player->set_ammo(ADD_AMMO);
}


         