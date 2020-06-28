#include <string>
#include <iostream>
#include <memory>

namespace mtm {
    class Character {
        protected:
        int health, ammo, range, power;
        public:
        Character() = delete;
        Character(int health,int ammo,int range,int power);
        virtual std::shared_ptr<Character> clone() const = 0;
        virtual ~Character();
    };
}