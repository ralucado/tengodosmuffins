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
    sf::FloatRect rect = getLocalBounds();
    sf::Vector2f pos = getPosition()+dist;
    if(collisionMap->getPixel(rect.left+pos.x,              rect.top+pos.y) == sf::Color(0,0,0)) return true;
    if(collisionMap->getPixel(rect.left+rect.width+pos.x,   rect.top+pos.y) == sf::Color(0,0,0)) return true;
    if(collisionMap->getPixel(rect.left+pos.x,              rect.top-rect.height+pos.y) == sf::Color(0,0,0)) return true;
    if(collisionMap->getPixel(rect.left+rect.width+pos.x,   rect.top-rect.height+pos.y) == sf::Color(0,0,0)) return true;
    return false;
}

