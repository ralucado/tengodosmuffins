#include "bullet.hpp"

Bullet::Bullet(Party*p, sf::Texture*tex, sf::Image*collisionMap, int numStates, int numFrames, sf::Vector2f mov, Player* pl) :
    Character(p, tex, collisionMap, numStates, numFrames),
    player(pl) {
    float scale = 0.2f;
    setScale(sf::Vector2f(scale,scale));
    setPosition(player->getPosition().x+player->getTextureRect().width*scale  , player->getPosition().y+player->getTextureRect().height*scale);
    this->mov = mov*speed;
    spriteSize = 64;
}

void Bullet::update(float deltaTime){
    collided = moveWithCollisions(mov*deltaTime);
    if(!collided) this->move(mov*deltaTime);
}

void Bullet::draw(sf::RenderWindow*window){
    window->draw(*this);
}

bool Bullet::hasCollided(){
    return collided;
}

sf::Vector2f Bullet::getMov() {
    return mov;
}


