#ifndef PLAYER_H
#define PLAYER_H
#include "Character.hpp"


class Player : public Character {
    public:
        Player(sf::Image* collisionMap);

        void update(float deltaTime);
        void draw(sf::RenderWindow* window);
        sf::Texture t;
};

#endif // PLAYER_H
