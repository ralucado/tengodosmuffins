#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include "commons.hpp"

class Character : public sf::Sprite {
    public:
        Character(sf::Image* collisionMap);

        void moveWithCollisions(sf::Vector2f dist);
        bool collides(sf::Vector2f dist);
    private:
        sf::Image* collisionMap = nullptr;
};

#endif // CHARACTER_HPP
