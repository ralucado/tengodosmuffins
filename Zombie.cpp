#include "Zombie.hpp"

sf::Vector2f normalize(const sf::Vector2f& source) {
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0) return sf::Vector2f(source.x / length, source.y / length);
    else return source;
}

Zombie::Zombie(sf::Texture* tex, sf::Image* collisionMap) : Character(tex, collisionMap) {
    setScale(sf::Vector2f(0.5f, 0.5f));
}

void Zombie::calcState() {
    std::pair<bool, sf::Vector2f> nearestPlayer = getNearestPlayerPos();
    if(!nearestPlayer.first) calcRandomState();
    else followPos(nearestPlayer.second);
    float min = 0.75f;
    float max = 1.25f;
    movementTimeLeft = min + (max-min)*((rand()%100)*0.01f);
}

std::pair<bool, sf::Vector2f> Zombie::getNearestPlayerPos() {
    return std::pair<bool, sf::Vector2f>(false, sf::Vector2f(0,0));
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
    (void) pos;
    ASSERT(false);
    return;
}

void Zombie::update(float deltaTime) {
    (void) deltaTime;
    movementTimeLeft -= deltaTime;

    // Move sprite
    bool collided = moveWithCollisions(getDispFromState()*deltaTime);

    if(collided && zombieState == Zombie::Walk)
        zombieState = Zombie::Idle;

    if(movementTimeLeft < 0.0f)
        calcState();

    int state = std::min((int)zombieState, 1);
    setAnimState(4*state+(int)direction);

    //nearest player
    //nearest seen player

    //set nearest alive player
        //nearest distance
    //set nearest seen alive player
        //raycasting between zombie an player

    //if nearest seen player != null
        //go towards nearest seen player

    // if nearest player != null
        //get last player checkpoint
        //get zombie last checkpoint
        //bfs between checkpoints
        //move towards nearest bfs checkpoint

    //if all null
        //move random between nearest checkpoints
}

void Zombie::draw(sf::RenderWindow* window) {
    window->draw(*this);
}
