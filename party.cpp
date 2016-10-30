#include "party.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Zombie.hpp"
#include "NoTengoMuffins.hpp"

Party::Party(){
    InputManager::bind(InputAction::moveX0, 0, sf::Joystick::Axis::X);
    InputManager::bind(InputAction::moveY0, 0, sf::Joystick::Axis::Y);
    InputManager::bind(InputAction::recharge0, 0, 4);
    InputManager::bind(InputAction::shot0, 0, 0);
    InputManager::bind(InputAction::moveX1, 1, sf::Joystick::Axis::X);
    InputManager::bind(InputAction::moveY1, 1, sf::Joystick::Axis::Y);
    InputManager::bind(InputAction::recharge1, 1, 4);
    InputManager::bind(InputAction::shot1, 1, 0);

    ASSERT(collisionMap.loadFromFile("Resources/BackgroundCollider.png"));
    ASSERT(backgroundMap.loadFromFile("Resources/Background.png"));
    ASSERT(zombieTex.loadFromFile("Resources/zombieMuffin.png"));
    ASSERT(playerTex.loadFromFile("Resources/mafin.png"));
    ASSERT(bulletTex.loadFromFile("Resources/ShittyPepitty.png"));
    players.push_back(new Player(this, &playerTex, &collisionMap,
        {
            InputAction::shot0,
            InputAction::recharge0,
            InputAction::moveX0,
            InputAction::moveY0
        } , 8 , 8
    ));
    players.push_back(new Player(this, &playerTex, &collisionMap,
        {
            InputAction::shot1,
            InputAction::recharge1,
            InputAction::moveX1,
            InputAction::moveY1
        } , 8 , 8
    ));
    for(int i = 0; i < 1; ++i)
        zombies.push_back(new Zombie(this, &zombieTex, &collisionMap,8,8));
    map = new Map(&backgroundMap);
}

Party::~Party(){
    for(auto p : players)
        delete p;
    for(auto p : zombies)
        delete p;
    for(auto p : bullets)
        delete p;

}

void Party::update(float deltaTime, sf::RenderWindow* window){
    InputManager::update();
    for(Player* p : players)
        p->update(deltaTime);
    for(Zombie* z : zombies)
        z->update(deltaTime);
    std::vector<Bullet*> toDelete;
    std::vector<Zombie*> toDeleteZombies;
    for(Bullet* b : bullets) {
        b->update(deltaTime);
        if(b->hasCollided()) {
            toDelete.push_back(b);
            continue;
        }
        for(Zombie* z : zombies) {
            sf::Vector2f diff = b->getPosition()-z->getPosition();
            float l = sqrt(diff.x*diff.x + diff.y+diff.y);
            if(l < 30) {
                toDeleteZombies.push_back(z);
                toDelete.push_back(b);
            }
        }
    }
}

void Party::draw(sf::RenderWindow*window){
    map->draw(window);
    for(Player* p : players)
        p->draw(window);
    for(Zombie* z : zombies)
        z->draw(window);
    for(Bullet* b : bullets)
        b->draw(window);
}

void Party::updateButtons(sf::Event e){

}

void Party::newShot(Player* id, sf::Vector2f dir){

    bullets.push_back(new Bullet(this,&bulletTex,&collisionMap,1,1,dir,id));
}
