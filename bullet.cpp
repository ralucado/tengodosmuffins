#include "bullet.hpp"

Bullet::Bullet(Party*p, sf::Texture*tex, sf::Image*collisionMap, int numStates, int numFrames, sf::Vector2f mov, Player* pl) :
    Character(p, tex, collisionMap, numStates, numFrames),
    player(pl) {
    setScale(sf::Vector2f(0.2f, 0.2f));
    setPosition(player->getPosition());
    this->mov = mov*speed;
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
