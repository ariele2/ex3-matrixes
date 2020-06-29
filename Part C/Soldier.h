#ifndef HW3_Soldier_H
#define HW3_Soldier_H
#include "Character.h"
#include "Auxiliaries.h"
#include "Exceptions.h"


namespace mtm {
    class Soldier : public Character {
        const int movement = 3;
        const int ADD_AMMO= 3;
        public:
        Soldier() = delete;
        Soldier(units_t health, units_t ammo, units_t range, units_t power,Team team);
        std::shared_ptr<Character> clone() const override;
        const int getMovement() const override;
        void attack(Matrix<std::shared_ptr<Character>>& game_board,
                     const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const override;
        void reload(Matrix<std::shared_ptr<Character>>& game_board, const GridPoint& coordinates) override;
    };
}

#endif