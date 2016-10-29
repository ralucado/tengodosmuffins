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

    std::vector<sf::Vector2f> points;
    points.push_back(sf::Vector2f(r.left+pos.x, r.top+pos.y));
    points.push_back(sf::Vector2f(r.left+r.width+pos.x, r.top+pos.y));
    points.push_back(sf::Vector2f(r.left+pos.x, r.top+r.height+pos.y));
    points.push_back(sf::Vector2f(r.left+r.width+pos.x, r.top+r.height+pos.y));
    float minX = 0;
    float maxX = p->getSize().x-1;
    float minY = 0;
    float maxY = p->getSize().y-1;
    for(auto& pt : points) {
        pt.x = clamp(pt.x, minX, maxX);
        pt.y = clamp(pt.y, minY, maxY);
        if(p->getPixel(pt.x, pt.y) == c)
            return true;
    }
    return false;
}

