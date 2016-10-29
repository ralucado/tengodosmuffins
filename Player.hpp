#ifndef PLAYER_H
#define PLAYER_H
#include "Character.hpp"
#include "InputManager.hpp"

class Player : public Character {
    using sf::Drawable::draw;

    public:
        struct Controls {
            InputAction shot;
            InputAction recharge;
            InputAction X;
            InputAction Y;
        };

        enum PlayerState {
            Idle = 0,
            Walk = 1
        };

        enum Direction {
            Down = 0,
            Left,
            Right,
            Up
        };

        Player(sf::Texture* tex, sf::Image* collisionMap, Controls pc);

        void update(float deltaTime);
        void draw(sf::RenderWindow* window);

    private:
        float speed = 500.0f;
        Controls controls;
        Direction direction = Down;
        PlayerState playerState = Idle;
};

#endif // PLAYER_H
