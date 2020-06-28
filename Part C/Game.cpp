#ifndef HW3_Game_H
#define HW3_Game_H
#include "Game.h"

using namespace mtm;
using namespace std;

Game::Game(int height, int width): height(height), width(width), board(board) {
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
    mtm::Character* new_player;
    if (type == SOLDIER) {
        new_player =  new mtm::Soldier(health, ammo, range, power);
    }
    else if (type == MEDIC) {
        new_player =  new mtm::Medic(health, ammo, range, power);
    }
    else {
        new_player =  new mtm::Sniper(health, ammo, range, power);
    }
}      






#endif