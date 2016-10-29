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

bool in_interval(float v, float lo, float hi) {
    return v >= lo && v <= hi;
}

bool Character::collides(sf::Vector2f dist)
{
    sf::FloatRect r = getLocalBounds();
    sf::Vector2f pos = getPosition()+dist;
    sf::Image* p = collisionMap;
    sf::Color c = sf::Color::Black;
    int size = 64;
    sf::Vector2f topleft = {r.left+pos.x, r.top+pos.y};
    std::vector<sf::Vector2f> colliders;
    for(int i = 0; i < size; i++) {
        colliders.push_back(topleft + sf::Vector2f(i, 0));
        colliders.push_back(topleft + sf::Vector2f(0, i));
        colliders.push_back(topleft + sf::Vector2f(size, i));
        colliders.push_back(topleft + sf::Vector2f(i, size));
    };
    float minX = 0;
    float maxX = p->getSize().x-1;
    float minY = 0;
    float maxY = p->getSize().y-1;
    for(auto& pt : colliders) {
        if(in_interval(pt.x, minX, maxX) && in_interval(pt.y, minY, maxY) && p->getPixel(pt.x, pt.y) == c)
            return true;
    }
    return false;
}

