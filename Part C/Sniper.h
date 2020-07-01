#ifndef HW3_SNIPER_H
#define HW3_SNIPER_H
#include "Character.h"
#include "Auxiliaries.h"
#include "Exceptions.h"

namespace mtm {
    class Sniper : public Character {
        const int movement = 4;
        int count_attacks = 1;
        const int DOUBLE_ATTACK_TIME = 3;
        const int ADD_AMMO = 2;
        public:
        Sniper() = delete;
        Sniper(int health, int ammo, int range, int power,Team team,CharacterType type);
        std::shared_ptr<Character> clone() const override;
        const int getMovement() const override;
        void updateAttacks() override;
        int getAttacks() const override;
        void attack(Matrix<std::shared_ptr<Character>>& game_board,
                     const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const override;
        void reload(Matrix<std::shared_ptr<Character>>& game_board,const GridPoint& coordinates) override;
    };
}
#endif