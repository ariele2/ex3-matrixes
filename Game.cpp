#ifndef HW3_Game_C
#define HW3_Game_C
#include "Game.h"
#include <vector>

using namespace mtm;
using namespace std;

Game::Game(int height, int width): height(height), width(width),board(board){
    if (height <= 0 || width <=0) {
        throw typename mtm::Matrix<shared_ptr<Character>>::IllegalInitialization(); //ILLEGAL ARGUMENT
    }
    Dimensions dims(height,width);
    Matrix<shared_ptr<Character>> board(dims);
}

Game::Game(const Game& other): height(other.height),width(other.width), board(other.board) {
    if (height <= 0 || width <=0) {
        throw typename mtm::Matrix<Character*>::IllegalInitialization(); //ILLEGAL ARGUMENT
    }
    Dimensions dims(other.height,other.width);
    for (int i=0; i<(*this).board.height(); i++) {
        for (int j=0 ;j<(*this).board.width(); j++) {
            shared_ptr<Character> new_ptr(other.board(i,j)->clone());
            (*this).board(i,j) = new_ptr;
        }
    }
}

Game& Game::operator=(const Game& other) {
    if(this == &other){
        return *this;
    }
    (*this).height = other.height;
    (*this).width = other.width;
    (*this).board = other.board;
    return (*this);
}

void Game::addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character) {
    //exceptions
    (*this).board(coordinates.row,coordinates.col) = character;
}
   
std::shared_ptr<mtm::Character> makeCharacter(CharacterType type, Team team,
                                        units_t health, units_t ammo, units_t range, units_t power) {
    //exceptions
    
    if (type == SOLDIER) {
        return shared_ptr<mtm::Character>(new Soldier(health, ammo, range, power, team));
    }
    else if (type == MEDIC) {
       return shared_ptr<mtm::Character>(new Medic(health, ammo, range, power,team));
    }
    else {
        return shared_ptr<mtm::Character>(new Sniper(health, ammo, range, power,team));
    }
}      

void Game::move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) {
    //exceptions
    shared_ptr<Character> player = this->board(src_coordinates.row, src_coordinates.col);
    int unit_movement = player->move();
    addCharacter(dst_coordinates, player);
}

void Game::attack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) {
    //exceptions
    shared_ptr<Character> player(this->board(src_coordinates.row, src_coordinates.col));
    player->attack(*this, src_coordinates, dst_coordinates);
}

void Game::reload(const GridPoint& coordinates) {
    shared_ptr<Character> player(this->board(coordinates.row, coordinates.col));
    player->reload(*this, coordinates);
}
    





#endif