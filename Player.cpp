#include "Player.hpp"
#include "InputManager.hpp"
#include "party.hpp"

Player::Player(Party* p,sf::Texture* tex, sf::Texture* texFace, sf::Image* collisionMap, Player::Controls pc, int numStates, int numFrames) : Character(p, texFace, collisionMap, numStates, numFrames), controls(pc) {
    shots = maxshots;
    setScale(sf::Vector2f(0.5f, 0.5f));
    spriteSize = 128;
    score = 0;
    backTex.setPosition(960, 340);
    backTex.setTexture(*tex);
    backTex.setScale(sf::Vector2f(0.5f, 0.5f));
    updateBackTextureRect();
}

void Player::updateBackTextureRect() {
    backTex.setTextureRect(sf::IntRect(shots*spriteSize, direction*spriteSize, spriteSize, spriteSize));
}

void Player::push(sf::Vector2f impulse) {
    pushImpulse = impulse;
    pushingTime = totalPushingTime;
}


void Player::upScore(int amount){
    score+=amount;
}

int Player::getScore(){
    return score;
}

void Player::update(float deltaTime)
{
    shootCooldown = std::max(0.0f, shootCooldown-deltaTime);
    pushingTime = std::max(0.0f, pushingTime-deltaTime);
    bool recharging = InputManager::action(controls.recharge);
    if(recharging && shots < maxshots) {
        playerState = Player::Recharge;
        direction = Player::Down;
        rechargeTimeCounter -= deltaTime;
        if(rechargeTimeCounter <= 0) {
            newBulletTimeCounter -= deltaTime;
            if(newBulletTimeCounter <= 0) {
                newBulletTimeCounter = newBulletTime;
                ++shots;
            }
        }
    }
    else {
        rechargeTimeCounter = rechargeTime;
        newBulletTimeCounter = 0;
        // Get input
        float dx = InputManager::action(controls.X);
        float dy = InputManager::action(controls.Y);
        float MIN = 0.2f;
        if(std::abs(dx) < MIN) dx = 0.0f;
        if(std::abs(dy) < MIN) dy = 0.0f;
        dx = dx*deltaTime*speed;
        dy = dy*deltaTime*speed;
        bool shot = InputManager::action(controls.shot);

        // Move sprite
        moveWithCollisions(sf::Vector2f(dx, dy));

        // Calc anim state
        playerState = (std::abs(dx) > 0.0f || std::abs(dy) > 0.0f)? Player::Walk : Player::Idle;
        if(playerState == Player::Walk) {
            if(std::abs(dy) >= std::abs(dx)) direction = dy > 0 ? Player::Down : Player::Up;
            else direction = dx > 0 ? Player::Right: Player::Left;
        }

        //shoot
        if(shot && shots > 0 && shootCooldown == 0.0f) disparar();
    }
    if(pushingTime > 0.0f) moveWithCollisions(pushImpulse*deltaTime*(pushingTime/totalPushingTime));
    backTex.setPosition(getPosition());
    setAnimState(((int)playerState)*4+((int)direction));
    updateBackTextureRect();
    updateAnimState(deltaTime);
}

void Player::draw(sf::RenderWindow* window) {
    window->draw(backTex);
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
    shootCooldown = .3f;
}
