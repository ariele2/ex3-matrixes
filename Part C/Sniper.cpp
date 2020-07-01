#ifndef HW3_SNIPER_C
#define HW3_SNIPER_C
#include "Sniper.h"



using namespace mtm;
using namespace std;

shared_ptr<Character> Sniper::clone() const {
    shared_ptr<Sniper> ptr(new Sniper(*this));
    return ptr;
}

Sniper::Sniper(int health, int ammo, int range, int power,Team team,CharacterType type): 
    Character(health,ammo,range,power,team,type) {}

const int Sniper::getMovement() const{
    return movement;
}

void Sniper::updateAttacks() {
    count_attacks++;
}

int Sniper::getAttacks() const {
    return count_attacks;
}

void Sniper::attack(Matrix<shared_ptr<Character>>& game_board,const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const {
    shared_ptr<Character> attacking_player = game_board(src_coordinates.row, src_coordinates.col);
    units_t unreachable_area = ceil(static_cast<double>(attacking_player->getRange())/2);
    int attack_distance = GridPoint::distance(src_coordinates, dst_coordinates);
    if(attack_distance < unreachable_area || attack_distance > attacking_player->getRange()) {
        throw typename mtm::OutOfRange();
    }
    else if (attacking_player->getAmmo() == 0) {
        throw typename mtm::OutOfAmmo();
    }
    shared_ptr<Character> attacked_player(game_board(dst_coordinates.row, dst_coordinates.col));
    if(!attacked_player || attacking_player->getTeam() == attacked_player->getTeam()){
        throw typename mtm::IllegalTarget();
    }
    if (attacking_player->getAttacks() % DOUBLE_ATTACK_TIME == 0) {
        attacked_player->setHealth(-2*attacking_player->getPower());
    }
    else {
        attacked_player->setHealth(-attacking_player->getPower());
    }
    if(attacked_player->getHealth() == 0) {
        attacked_player = nullptr;
        game_board(dst_coordinates.row, dst_coordinates.col) = nullptr;
    }
    attacking_player->updateAttacks();
    attacking_player->setAmmo(AMMO_DOWN);
}

void Sniper::reload(Matrix<shared_ptr<Character>>& game_board,const GridPoint& coordinates) {
    shared_ptr<Character> curr_player = game_board(coordinates.row, coordinates.col);
    curr_player->setAmmo(ADD_AMMO);
}
   

#endif