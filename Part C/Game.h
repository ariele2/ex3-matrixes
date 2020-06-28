#include "Auxiliaries.h"
#include "Soldier.h"
#include "Sniper.h"
#include "Medic.h"
#include "Matrix.h"
#include "Character.h"
#include <memory>
#include <iostream>

namespace mtm {
    class Game {
        int height ,width;
        Matrix<std::shared_ptr<Character>> board;  
        public:
        Game() = delete;
        Game(int height, int width);
        ~Game() = default;
        Game (const Game& other);
        Game& operator=(const Game& other);
        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                                        units_t health, units_t ammo, units_t range, units_t power);
        
    };
}