#ifndef HW3_Game_H
#define HW3_Game_H
#include "Auxiliaries.h"
#include "Soldier.h"
#include "Sniper.h"
#include "Medic.h"
#include "Matrix.h"
#include "Exceptions.h"
#include <vector>
#include <memory>
#include <iostream>

namespace mtm {
    class Game {
        int height ,width;
        Matrix<std::shared_ptr<mtm::Character>> board; 
        public:
        Game() = delete;
        // constructor - recieves the height and width of the game board.
        Game(int height, int width);
        ~Game() = default;
        // copy construcor - makes a deep copy of a game.
        Game (const Game& other);
        // operator= - makes a deep copy of a game, to a game that already initialized.
        Game& operator=(const Game& other);
        // makes a new character, receiving all the neccessary parameters of a character.
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                                        units_t health, units_t ammo, units_t range, units_t power);
        // adds a premade character (with makeCharacter) to a coordinates entered by the user.
        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
        // moves a character from a source coordinates to a destiny coordinates.
        void move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates); 
        // attacks a character on the destiny coordinates, by a character on the source coordinates. 
        void attack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
        //reloads the ammo of the character on the entered coordinates.
        void reload(const GridPoint& coordinates);
        // checks if one of the teams won, if so - returns true. also updates a pointer (if entered) that
        // tells who is the winning team.
        bool isOver(Team* winningTeam=NULL) const;
        // operator<< : use it to print the game board to the output terminal.
        friend std::ostream& operator<<(std::ostream& os,const Game& game){
            std::vector<char> board_vector;
            for (int i=0; i<game.height; i++) {
                for (int j=0; j<game.width; j++) {
                    std::shared_ptr<Character> player = game.board(i,j);
                    if(player == nullptr){
                        board_vector.push_back(' ');
                    }
                    else if (player->getType() == SOLDIER) {
                            if (player->getTeam() == CPP) {
                                board_vector.push_back('S');
                            }
                            else {
                                board_vector.push_back('s');
                            }
                        }
                    else if (player->getType() == MEDIC) { 
                            if (player->getTeam() == CPP) {
                                board_vector.push_back('M');
                            }
                            else {
                                board_vector.push_back('m');
                            }
                        }  
                    else if (player->getType() == SNIPER){
                            if (player->getTeam() == CPP) {
                                board_vector.push_back('N');
                            }
                            else {
                                board_vector.push_back('n');
                            }
                        }
                    }
                }
            return printGameBoard(os,board_vector.data(),board_vector.data() + board_vector.size(),game.width);
        }
    };
}
#endif