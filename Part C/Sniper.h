#ifndef HW3_Sniper_H
#define HW3_Sniper_H
#include "Character.h"


namespace mtm {
    class Sniper : public Character {
        const int movement = 4;
        int count_attacks = 1;
        const int DOUBLE_ATTACK_TIME = 3;
        const int ADD_AMMO = 2;
        public:
        Sniper() = delete;
        Sniper(int health, int ammo, int range, int power,Team team);
        std::shared_ptr<Character> clone() const override;
        const int getMovement() const override;
        void updateAttacks();
        int get_attacks() const;
        void attack(Matrix<std::shared_ptr<Character>>& game_board,
                     const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const override;
        void reload(Matrix<std::shared_ptr<Character>>& game_board,const GridPoint& coordinates) override;
    };
}
#endif