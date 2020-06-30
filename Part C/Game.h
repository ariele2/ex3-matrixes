#ifndef HW3_Game_H
#define HW3_Game_H
#include "Auxiliaries.h"
#include "Soldier.h"
#include "Sniper.h"
#include "Medic.h"
#include "Matrix.h"
#include "Character.h"
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
        Game(int height, int width);
        ~Game() = default;
        Game (const Game& other);
        Game& operator=(const Game& other);
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                                        units_t health, units_t ammo, units_t range, units_t power);
        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
        void move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);  
        void attack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
        void reload(const GridPoint& coordinates);
        bool isOver(Team* winningTeam=NULL) const;
        friend std::ostream& operator<<(std::ostream& os,const Game& game){
            std::vector<char> board_vector;
            for (int i=0; i<game.height; i++) {
                for (int j=0; j<game.width; j++) {
                    std::shared_ptr<Character> player(game.board(i,j));
                    if (typeid(player) == typeid(Soldier)){
                        if (player->getTeam() == CPP) {
                            board_vector.push_back('S');
                        }
                        else {
                            board_vector.push_back('s');
                    }
                }
                if (typeid(player) == typeid(Medic)){
                    if (player->getTeam() == CPP) {
                        board_vector.push_back('M');
                    }
                    else {
                        board_vector.push_back('m');
                    }
                }
                if (typeid(player) == typeid(Sniper)){
                    if (player->getTeam() == CPP) {
                        board_vector.push_back('N');
                    }
                    else {
                        board_vector.push_back('n');
                    }
                }
                else {
                    board_vector.push_back(' ');
                }
            }
        }
        return printGameBoard(os,board_vector.data(),board_vector.data() + board_vector.size(),game.width);
        }
    };
}
#endif