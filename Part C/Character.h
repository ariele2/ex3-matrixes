#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <iostream>
#include <memory>
#include "Auxiliaries.h"
#include "Game.h"
#include <vector>
#include <math.h>
#include "Matrix.h"

namespace mtm {
    class Character {
        protected:
        units_t health, ammo, range, power;
        Team team;
        const int AMMO_DOWN = -1;
        public:
        Character() = delete;
        Character(units_t health,units_t ammo,units_t range,units_t power,Team team);
        virtual std::shared_ptr<Character> clone() const = 0;
        virtual ~Character();
        const units_t getHealth();
        const units_t getAmmo();
        const units_t getRange();
        const units_t getPower();
        const Team getTeam();
        void setHealth(int health_change);
        void setAmmo(int ammo_change);
        virtual const int getMovement() const = 0;
        virtual void attack(mtm::Matrix<std::shared_ptr<Character>>& game_board, 
                            const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const = 0;
        virtual void reload(mtm::Matrix<std::shared_ptr<Character>>& game_board, const GridPoint& coordinates) = 0;
        class OutOfRange;
    };
}

#endif 