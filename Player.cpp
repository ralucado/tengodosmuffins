#include "Player.hpp"
#include "InputManager.hpp"
#include "party.hpp"

Player::Player(Party* p,sf::Texture* tex, sf::Image* collisionMap, Player::Controls pc, int numStates, int numFrames) : Character(p, tex, collisionMap, numStates, numFrames), controls(pc) {
    shots = maxshots;
    setScale(sf::Vector2f(0.5f, 0.5f));
    spriteSize = 128;
}

void Player::update(float deltaTime)
{
    // Get input
    float dx = InputManager::action(controls.X)*deltaTime*speed;
    float dy = InputManager::action(controls.Y)*deltaTime*speed;
    bool shot = InputManager::action(controls.shot);
    float MIN = 0.3f;
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

    if(shot && shots > 0) disparar();

    setAnimState(((int)playerState)*4+((int)direction));
    updateAnimState(deltaTime);
}

void Player::draw(sf::RenderWindow* window) {
    window->draw(*this);
}

void Player::disparar(){
    --shots;
    sf::Vector2f dir = sf::Vector2f(0,0);
    if(direction == Player::Up) dir.y = -1;
    else if (direction == Player::Down) dir.y = 1;
    else if (direction == Player::Right) dir.x = 1;
    else dir.x = -1;
    scene->newShot(this, dir);
}
