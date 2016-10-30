#include "Zombie.hpp"
#include "Player.hpp"
#include "party.hpp"

sf::Vector2f normalize(const sf::Vector2f& source) {
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0) return sf::Vector2f(source.x / length, source.y / length);
    else return source;
}

Zombie::Zombie(Party* p, sf::Texture* tex, sf::Image* collisionMap, int nS, int nF) : Character(p, tex, collisionMap, nS, nF) {
    setScale(sf::Vector2f(0.5f, 0.5f));
    spriteSize = 128;
}

void Zombie::calcState() {
    std::pair<bool, sf::Vector2f> nearestPlayer = getNearestPlayerPos();
    if(!nearestPlayer.first) calcRandomState();
    else followPos(nearestPlayer.second);
    float min = 0.1f;
    float max = 2.0f;
    movementTimeLeft = min + (max-min)*((rand()%100)*0.01f);
}

std::pair<bool, sf::Vector2f> Zombie::getNearestPlayerPos() {
    float bestDist = -1;
    sf::Vector2f bestPos;
    sf::Vector2f myPos= getPosition();
    for(Player* p : scene->getPlayers()) {
        sf::Vector2f diff = p->getPosition()-myPos;
        float len = sqrt((diff.x * diff.x) + (diff.y * diff.y));
        sf::Vector2f norm = normalize(diff);

        bool collided = false;
        for(int i = 0; i < len; ++i) {
            if(checkPixel(myPos+norm*(float)i, sf::Color::Black)) {
                collided = true;
                break;
            }
        }
        if(!collided && (bestDist < 0 || bestDist > len)) {
                bestDist = len;
                bestPos = p->getPosition();
        }
    }
    return std::pair<bool, sf::Vector2f>(bestDist > 0, bestPos);
}

void Zombie::calcRandomState() {
    zombieState = (rand() % 5 == 1) ? Zombie::Idle : Zombie::Walk;
    direction = (Zombie::Direction)(rand()%4);
}

sf::Vector2f Zombie::getDispFromState() {
    switch(zombieState) {
        case Zombie::Idle:
            return sf::Vector2f(0, 0);
            break;
        case Zombie::Walk:
            switch(direction) {
                case Zombie::Left:
                    return sf::Vector2f(-walkSpeed, 0);
                    break;
                case Zombie::Right:
                    return sf::Vector2f(walkSpeed, 0);
                    break;
                case Zombie::Up:
                    return sf::Vector2f(0, -walkSpeed);
                    break;
                case Zombie::Down:
                    return sf::Vector2f(0, walkSpeed);
                    break;
            }
            break;
        case Zombie::Chase:
            return normalize(chasingPoint-getPosition())*chaseSpeed;
            break;
    }
    return sf::Vector2f(0, 0);
}

void Zombie::followPos(sf::Vector2f pos) {
    chasingPoint = pos;
    zombieState = Zombie::Chase;
    sf::Vector2f diff = pos-getPosition();
    if(std::abs(diff.x) < 1 && std::abs(diff.y) < 1)
        calcRandomState();
    if(std::abs(diff.y) > std::abs(diff.x)) direction = (diff.y > 0) ? Zombie::Down : Zombie::Up;
    else direction = (diff.x > 0) ? Zombie::Right : Zombie::Left;
}

void Zombie::update(float deltaTime) {
    movementTimeLeft -= deltaTime;

    // Move sprite
    bool collided = moveWithCollisions(getDispFromState()*deltaTime);

    if(collided && zombieState == Zombie::Walk)
        zombieState = Zombie::Idle;

    if(movementTimeLeft < 0.0f)
        calcState();

    int state = std::min((int)zombieState, 1);
    setAnimState(4*state+(int)direction);
    updateAnimState(deltaTime);

    for(Player* p : scene->getPlayers()) {
        if(getGlobalBounds().intersects(p->getGlobalBounds())){
            p->kill();
        }
    }
}

void Zombie::draw(sf::RenderWindow* window) {
    window->draw(*this);
}
