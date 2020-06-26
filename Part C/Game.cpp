#ifndef HW3_Game_H
#define HW3_Game_H
#include "Game.h"

using namespace mtm;

Game::Game(int height, int width): height(height), width(width) {
    if (height <= 0 || width <=0) {
        throw typename mtm::Matrix<Character*>::IllegalInitialization(); //ILLEGAL ARGUMENT
    }
    Dimensions dims(height,width);
    Matrix<Character*> board(dims);
}

Game::Game(const Game& other): height(other.height),width(other.width) {
    if (height <= 0 || width <=0) {
        throw typename mtm::Matrix<Character*>::IllegalInitialization(); //ILLEGAL ARGUMENT
    }
    Dimensions dims(height,width);
    for (int i=0; i<(*this).board.height(); i++) {
        for (int j=0 ;j<(*this).board.width(); j++) {
            (*this).board(i,j) = ((other.board)(i,j)).clone();
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
    (*this).board(coordinates.row,coordinates.col) = character.get();
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