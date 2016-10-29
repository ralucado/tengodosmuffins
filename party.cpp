#include "party.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Zombie.hpp"

Party::Party(){
    InputManager::bind(InputAction::moveX0, 0, sf::Joystick::Axis::X);
    InputManager::bind(InputAction::moveY0, 0, sf::Joystick::Axis::Y);
    InputManager::bind(InputAction::recharge0, 0, 4);
    InputManager::bind(InputAction::shot0, 0, 0);
    InputManager::bind(InputAction::moveX1, 1, sf::Joystick::Axis::X);
    InputManager::bind(InputAction::moveY1, 1, sf::Joystick::Axis::Y);
    InputManager::bind(InputAction::recharge1, 1, 4);
    InputManager::bind(InputAction::shot1, 1, 0);

    ASSERT(collisionMap.loadFromFile("Resources/BackgroundTest.png"));
    ASSERT(zombieTex.loadFromFile("Resources/zombieMuffin.png"));
    ASSERT(playerTex.loadFromFile("Resources/mafin.png"));
    player1 = new Player(&playerTex, &collisionMap,
        {
            InputAction::shot0,
            InputAction::recharge0,
            InputAction::moveX0,
            InputAction::moveY0
        }
    );
    player2 = new Player(&playerTex, &collisionMap,
        {
            InputAction::shot1,
            InputAction::recharge1,
            InputAction::moveX1,
            InputAction::moveY1
        }
    );
    zombies.push_back(new Zombie(&zombieTex, &collisionMap));
    map = new Map(&collisionMap);
}

Party::~Party(){
    delete player1;
    delete player2;
}

void Party::update(float deltaTime, sf::RenderWindow* window){
    InputManager::update();
    player1->update(deltaTime);
    player2->update(deltaTime);
    for(Zombie* z : zombies)
        z->update(deltaTime);
}

void Party::draw(sf::RenderWindow*window){
    map->draw(window);
    player1->draw(window);
    player2->draw(window);
    for(Zombie* z : zombies)
        z->draw(window);
}

void Party::updateButtons(sf::Event e){
}
