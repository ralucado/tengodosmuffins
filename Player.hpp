#ifndef PLAYER_H
#define PLAYER_H
#include "Character.hpp"
#include "InputManager.hpp"

struct PlayerControls {
    InputAction shot;
    InputAction recharge;
    InputAction X;
    InputAction Y;
};

class Player : public Character {
    using sf::Drawable::draw;

    public:
        Player(sf::Image* collisionMap, PlayerControls pc);

        void update(float deltaTime);
        void draw(sf::RenderWindow* window);

    private:
        sf::Texture t;
        float speed = 500.0f;
        PlayerControls controls;
};

#endif // PLAYER_H
