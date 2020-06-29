#include "Sniper.h"

using namespace mtm;
using namespace std;

shared_ptr<Character> Sniper::clone() const {
    shared_ptr<Sniper> ptr(new Sniper(*this));
    return ptr;
}

Sniper::Sniper(int health, int ammo, int range, int power,Team team): 
    Character(health,ammo,range,power,team) {}

const int Sniper::move() const{
    return movement;
}

void Sniper::updateAttacks(){
    count_attacks++;
}

int Sniper::get_attacks() const {
    return count_attacks;
}

void Sniper::attack(Game& game,const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const {
    shared_ptr<Sniper> attacking_player(game.board(src_coordinates.row, src_coordinates.col));
    units_t unreachable_area = ceil(static_cast<double>(attacking_player->get_range())/2);
    int attack_distance = GridPoint::distance(src_coordinates, dst_coordinates);
    if(attack_distance >= unreachable_area && attack_distance <= attacking_player->get_range()) {
        shared_ptr<Character> attacked_player(game.board(src_coordinates.row, src_coordinates.col));
        if (attacking_player->get_attacks() % DOUBLE_ATTACK_TIME == 0) {
            attacked_player->set_health(-2*attacking_player->get_power());
        }
        else {
            attacked_player->set_health(-attacking_player->get_power());
        }
        if(attacked_player->get_health() == 0) {
            attacked_player = nullptr;
            game.board(dst_coordinates.row, dst_coordinates.col) = nullptr;
        }
    }
    attacking_player->updateAttacks();
    attacking_player->set_ammo(AMMO_DOWN);
}

void Sniper::reload(Game& game,const GridPoint& coordinates) {
    //exceptions
    shared_ptr<Soldier> curr_player(game.board(coordinates.row, coordinates.col));
    curr_player->set_ammo(ADD_AMMO);
}
   