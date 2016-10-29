#include "Character.hpp"

Character::Character(sf::Image* collisionMap) : collisionMap(collisionMap) {
}

void Character::moveWithCollisions(sf::Vector2f dist) {
    if(collides(sf::Vector2f(dist.x, 0))) {
        float min = 0;
        float max = 1;
        while(max-min > 0.001) { //search for the maximum distance you can move
            float m = (max+min)/2;
            if(collides(sf::Vector2f(dist.x*m, 0)))
                max = m;
            else
                min = m;
        }
        dist.x *= min;
    }

    if(collides(sf::Vector2f(0, dist.y))) {
        float min = 0;
        float max = 1;
        while(max-min > 0.001) { //search for the maximum distance you can move
            float m = (max+min)/2;
            if(collides(sf::Vector2f(0, dist.y*m)))
                max = m;
            else
                min = m;
        }
        dist.y *= min;
    }
    move(dist);
}

bool Character::collides(sf::Vector2f dist)
{
    sf::FloatRect r = getLocalBounds();
    sf::Vector2f pos = getPosition()+dist;
    sf::Image* p = collisionMap;
    sf::Color c = sf::Color::Black;

    if(
       p->getPixel(r.left+pos.x, r.top+pos.y) == c ||
       p->getPixel(r.left+r.width+pos.x, r.top+pos.y) == c ||
       p->getPixel(r.left+pos.x, r.top+r.height+pos.y) == c ||
       p->getPixel(r.left+r.width+pos.x, r.top+r.height+pos.y) == c
    )
        return true;
    return false;
}

