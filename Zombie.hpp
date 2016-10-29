#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "Character.hpp"


class Zombie : public Character {
    public:
        Zombie(sf::Image* collisionMap);

        void update(float deltaTime);
};

#endif // ZOMBIE_H
