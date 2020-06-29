#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <iostream>
#include <memory>
#include "Auxiliaries.h"
#include "Game.h"
#include <vector>
#include <math.h>

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
        const units_t get_health();
        const units_t get_ammo();
        const units_t get_range();
        const units_t get_power();
        const Team get_team();
        void set_health(int health_change);
        void set_ammo(int ammo_change);
        virtual const int move() const = 0;
        virtual void attack(Game& game,const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const = 0;
        virtual void reload(Game& game,const GridPoint& coordinates) = 0;
    };
}

#endif 