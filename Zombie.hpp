#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "Character.hpp"

class Zombie : public Character {
    using sf::Drawable::draw;

    public:
        enum ZombieState {
            Idle = 0,
            Walk,
            Chase
        };

        enum Direction {
            Down = 0,
            Left,
            Right,
            Up
        };

        Zombie(sf::Texture* tex, sf::Image* collisionMap);

        void update(float deltaTime);
        void draw(sf::RenderWindow* window);

    private:
        std::pair<bool, sf::Vector2f> getNearestPlayerPos();
        void calcRandomState();
        sf::Vector2f getDispFromState();
        void followPos(sf::Vector2f pos);
        void calcState();

        float walkSpeed = 150.0f;
        float chaseSpeed = 200.0f;
        sf::Vector2f chasingPoint;
        Direction direction = Down;
        ZombieState zombieState = Idle;
        float movementTimeLeft = 0.0f;
};

#endif // ZOMBIE_H
