#include "Player.hpp"
#include "InputManager.hpp"

Player::Player(sf::Image* collisionMap) : Character(collisionMap) {
    ASSERT(t.loadFromFile("Resources/buttontejempl2.png"));
    setTexture(t);
    setTextureRect(sf::IntRect(0, 0, 64, 64));
}

void Player::update(float deltaTime)
{
    float dx = InputManager::action(InputAction::moveX0)*deltaTime*speed;
    float dy = InputManager::action(InputAction::moveY0)*deltaTime*speed;
    moveWithCollisions(sf::Vector2f(dx, dy));
    //animation states: idle, moving left/right/up/down, shoot (idle, while moving), recharge
    //action states: idle, moving, recharging
    /*
    if nothing  pressed
        do idle
    if move buttons pressed
        do moving
    if recharge pressed
        do recharge
    if shoot pressed
        shoot
    */
}

void Player::draw(sf::RenderWindow* window) {
    window->draw(*this);
}
