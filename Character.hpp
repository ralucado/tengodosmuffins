#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include "commons.hpp"

class Character : public sf::Sprite {
    public:
        Character();

        void moveWithCollisions(sf::Vector2f dist, sf::Image& collisionMap);
        bool collides(sf::Image& collision, sf::Vector2f dist);
};

#endif // CHARACTER_HPP
