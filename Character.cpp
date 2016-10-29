#include "Character.hpp"

Character::Character() {
}

void Character::moveWithCollisions(sf::Vector2f dist, sf::Image& collisionMap) {
    if(collides(collisionMap, sf::Vector2f(dist.x, 0)) {
        float min = 0;
        float max = 1;
        while(max-min > 0.001) { //search for the maximum distance you can move
            float m = (max+min)/2;
            if(collides(collisionMap, sf::Vector2f(dist.x*m, 0))
                max = m;
            else
                min = m;
        }
        dist.x *= min;
    }

    if(collides(collisionMap, sf::Vector2f(0, dist.y)) {
        float min = 0;
        float max = 1;
        while(max-min > 0.001) { //search for the maximum distance you can move
            float m = (max+min)/2;
            if(collides(collisionMap, sf::Vector2f(0, dist.y*m))
                max = m;
            else
                min = m;
        }
        dist.y *= min;
    }
    //move dist safely
}

bool Character::collides(sf::Image& collision)
{

}

