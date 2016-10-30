#include "Player.hpp"
#include "InputManager.hpp"

Player::Player(Party* p,sf::Texture* tex, sf::Image* collisionMap, Player::Controls pc) : Character(p, tex, collisionMap), controls(pc) {
}

void Player::update(float deltaTime)
{
    setScale(sf::Vector2f(0.5f, 0.5f));
    // Get input
    float dx = InputManager::action(controls.X)*deltaTime*speed;
    float dy = InputManager::action(controls.Y)*deltaTime*speed;
    float MIN = 0.2f;
    if(std::abs(dx) < MIN) dx = 0.0f;
    if(std::abs(dy) < MIN) dy = 0.0f;

    // Move sprite
    moveWithCollisions(sf::Vector2f(dx, dy));

    // Calc anim state
    playerState = (std::abs(dx) > 0.0f || std::abs(dy) > 0.0f)? Player::Walk : Player::Idle;
    if(playerState == Player::Walk) {
        if(std::abs(dy) >= std::abs(dx)) direction = dy > 0 ? Player::Down : Player::Up;
        else direction = dx > 0 ? Player::Right: Player::Left;
    }
    setAnimState(((int)playerState)*4+((int)direction));
    updateAnimState(deltaTime);
}

void Player::draw(sf::RenderWindow* window) {
    window->draw(*this);
}
