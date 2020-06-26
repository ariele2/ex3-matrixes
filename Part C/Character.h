#include <string>
#include <iostream>

namespace mtm {
    class Character {
        protected:
        int health, ammo, range, power;
        public:
        Character() = delete;
        Character(int health,int ammo,int range,int power);
        virtual Character* clone() const = 0;
        virtual ~Character();
    };
}