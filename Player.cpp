#include "Player.hpp"
#include "InputManager.hpp"

Player::Player(sf::Image* collisionMap, PlayerControls pc) : Character(collisionMap), controls(pc) {
    ASSERT(t.loadFromFile("Resources/buttontejempl2.png"));
    setTexture(t);
    setTextureRect(sf::IntRect(0, 0, 64, 64));
}

void Player::update(float deltaTime)
{
    float dx = InputManager::action(controls.X)*deltaTime*speed;
    float dy = InputManager::action(controls.Y)*deltaTime*speed;
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
