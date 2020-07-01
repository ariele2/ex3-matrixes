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
        // constructor - receivs 6 parameters.
        Character(units_t health,units_t ammo,units_t range,units_t power,Team team, CharacterType type);
        // makes a clone to a shared pointer of the classes derived from Character.
        virtual std::shared_ptr<Character> clone() const = 0;
        virtual ~Character() = default;
        // returns the health of the current Character.
        const units_t getHealth();
        // returns the ammo of the current Character.
        const units_t getAmmo();
        // returns the range of the current Character.
        const units_t getRange();
        // returns the power of the current Character.
        const units_t getPower();
        // returns the team of the current Character.
        const Team getTeam();
        // returns the type of the current Character.
        const CharacterType getType();
        // sets the health of the Character, receiving the amount of health to change.
        void setHealth(int health_change);
        // sets the ammo of the Character, receiving the amount of ammo to change.
        void setAmmo(int ammo_change);
        // returns the movement (number of steps allowed) of the current Character.
        virtual const int getMovement() const = 0;
        // returns the number of attacks the character have made
        // (used only inside some of the classes that need the counter) 
        virtual int getAttacks() const{
            return 0;
        }
        // updates the number of attacks the character have made
        // (used only inside some of the classes that need the counter) 
        virtual void updateAttacks(){
            return;
        }
        //  attacks a character by source and destiny coordinates recievd from the user
        //  also, recievs the board to make the attack on.
        virtual void attack(mtm::Matrix<std::shared_ptr<Character>>& game_board, 
                            const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const = 0;
        // reloads the character ammo, by the coordinates recieved from the user.
        // also, recievs the board to make the attack on.
        virtual void reload(mtm::Matrix<std::shared_ptr<Character>>& game_board, const GridPoint& coordinates) = 0;
        class OutOfRange;
    };
}

#endif 