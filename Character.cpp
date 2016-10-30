#include "Character.hpp"

Character::Character(Party* p, sf::Texture* tex, sf::Image* collisionMap, int nStates, int nFrames) : scene(p), t(tex), collisionMap(collisionMap) {
    setPosition(960, 340);
    setTexture(*tex);
    updateTextureRect();
    numStates = nStates;
    numFrames = nFrames;
}

void Character::updateTextureRect() {
    setTextureRect(sf::IntRect(currFrame*spriteSize, currState*spriteSize, spriteSize, spriteSize));
}

void Character::setAnimState(unsigned int state) {
    currState = state;
    updateTextureRect();
}

unsigned int Character::getAnimState() {
    return currState;
}

void Character::updateAnimState(float deltaTime) {
    currTime += deltaTime;
    while(currTime >= frameTime) {
        currTime -= frameTime;
        currFrame = (currFrame+1)%numFrames;
        updateTextureRect();
    }
}

bool Character::moveWithCollisions(sf::Vector2f dist) {
    bool colliding = false;
    if(collides(sf::Vector2f(dist.x, 0))) {
        colliding = true;
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
        colliding = true;
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
    return colliding;
}

bool in_interval(float v, float lo, float hi) {
    return v >= lo && v <= hi;
}

bool Character::checkPixel(sf::Vector2f v, sf::Color c) {
    return (in_interval(v.x, 0, collisionMap->getSize().x-1) &&
            in_interval(v.y, 0, collisionMap->getSize().y-1) &&
            collisionMap->getPixel(v.x, v.y) == c);
}

bool Character::collides(sf::Vector2f dist)
{
    sf::FloatRect r = getLocalBounds();
    sf::Vector2f pos = getPosition()+dist;
    sf::Color c = sf::Color::Black;
    sf::Vector2f topleft = {r.left+pos.x, r.top+pos.y};
    for(int i = 0; i < spriteSize*getScale().x; i++) {
        if(checkPixel(topleft + sf::Vector2f(i, 0), c) ||
           checkPixel(topleft + sf::Vector2f(i, spriteSize*getScale().y), c))
            return true;
    }
    for(int i = 0; i < spriteSize*getScale().y; i++) {
        if(checkPixel(topleft + sf::Vector2f(0, i), c) ||
           checkPixel(topleft + sf::Vector2f(spriteSize*getScale().x, i), c)
           )
            return true;
    };
    return false;
}

