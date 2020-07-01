#ifndef HW3_MEDIC_H
#define HW3_MEDIC_H
#include "Character.h"
#include "Auxiliaries.h"
#include "Exceptions.h"



namespace mtm {
    class Medic : public mtm::Character {
        const int movement = 5;
        const int ADD_AMMO = 5;
        public:
        Medic() = delete;
        Medic(int health, int ammo, int range, int power,Team team,CharacterType type);
        std::shared_ptr<Character> clone() const override;
        const int getMovement() const override;
        void attack(Matrix<std::shared_ptr<Character>>& game_board ,
                    const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const override;
        void reload(Matrix<std::shared_ptr<Character>>& game_board ,const GridPoint& coordinates) override;
    };
}

#endif
