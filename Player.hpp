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
            Walk = 1,
            Recharge = 2
        };

        enum Direction {
            Down = 0,
            Left,
            Right,
            Up
        };

        Player(Party* p, sf::Texture* tex, sf::Texture* texFace, sf::Image* collisionMap, Controls pc, int numStates, int numFrames);

        void update(float deltaTime);
        void draw(sf::RenderWindow* window);
        void updateBackTextureRect();


    private:
        float speed = 300.0f;
        Controls controls;
        Direction direction = Down;
        PlayerState playerState = Idle;
        int shots;
        int maxshots = 7;
        float shootCooldown = 0.0f;
        float rechargeTimeCounter = 1.5f;
        float rechargeTime = 1.5f;
        float newBulletTimeCounter = 0.0f;
        float newBulletTime = .125f;
        void disparar();
        sf::Sprite backTex;
};

#endif // PLAYER_H
