#ifndef BULLET_HPP
#define BULLET_HPP
#include "commons.hpp"
#include "Player.hpp"

class Bullet : public Character {
        using sf::Drawable::draw;

    public:

        Bullet(Party* p, sf::Texture* tex, sf::Image* collisionMap, int numStates, int numFrames, sf::Vector2f mov, Player* pl);
        void update(float deltaTime);
        void draw(sf::RenderWindow* window);
        bool hasCollided();
        sf::Vector2f getMov();
        Player* player;

    private:
        float speed = 300;
        sf::Vector2f mov;
        bool collided = false;
};

#endif // BULLET_HPP
