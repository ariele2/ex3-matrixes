#ifndef HW3_Medic_H
#define HW3_Medic_H
#include "Character.h"


namespace mtm {
    class Medic : public Character {
        const int movement = 5;
        const int ADD_AMMO = 5;
        public:
        Medic() = delete;
        Medic(int health, int ammo, int range, int power,Team team);
        std::shared_ptr<Character> clone() const override;
        const int move() const override;
        void attack(Game& game,const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const override;
        void reload(Game& game,const GridPoint& coordinates) override;
    };
}

#endif
