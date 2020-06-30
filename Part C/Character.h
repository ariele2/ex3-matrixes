#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <iostream>
#include <memory>
#include "Auxiliaries.h"
#include <vector>
#include <math.h>
#include "Matrix.h"

namespace mtm {
    class Character {
        protected:
        units_t health, ammo, range, power;
        Team team;
        CharacterType type;
        const int AMMO_DOWN = -1;
        public:
        Character() = delete;
        Character(units_t health,units_t ammo,units_t range,units_t power,Team team,CharacterType type);
        virtual std::shared_ptr<Character> clone() const = 0;
        virtual ~Character() = default;
        virtual const units_t getHealth() = 0;
        virtual const units_t getAmmo() = 0;
        virtual const units_t getRange() = 0;
        virtual const units_t getPower()= 0;
        virtual const Team getTeam() = 0;
        virtual const CharacterType getType() = 0;
        virtual void setHealth(int health_change) = 0;
        virtual void setAmmo(int ammo_change) = 0;
        virtual const int getMovement() const = 0;
        virtual int getAttacks() const{
            return 0;
        }
        virtual void updateAttacks(){
            return;
        }
        virtual void attack(mtm::Matrix<std::shared_ptr<Character>>& game_board, 
                            const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const = 0;
        virtual void reload(mtm::Matrix<std::shared_ptr<Character>>& game_board, const GridPoint& coordinates) = 0;
        class OutOfRange;
    };
}

#endif 