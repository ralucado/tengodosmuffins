#include "NoTengoMuffins.hpp"
#include "InputManager.hpp"
#include "Map.hpp"

NoTengoMuffins::NoTengoMuffins() {

    //std::cout << "what " << std::endl;

    _scene = GameScene::menu;
    _scenes = std::vector<Scene*>(SCENE_NUM);
    //std::cout << "in menu" << std::endl;
    _scenes[GameScene::menu] = &_menu;

    InputManager::bind(InputAction::moveX0, 0, sf::Joystick::Axis::X);
    InputManager::bind(InputAction::recharge0, 0, 4);
    InputManager::bind(InputAction::shot0, 0, 0);
    InputManager::bind(InputAction::moveX1, 1, sf::Joystick::Axis::X);
    InputManager::bind(InputAction::recharge1, 1, 4);
    InputManager::bind(InputAction::shot1, 1, 0);

    ASSERT(collisionMap.loadFromFile("Resources/BackgroundTest.png"));
    player = new Player(&collisionMap);
    map = new Map(&collisionMap);
}

NoTengoMuffins::~NoTengoMuffins() {
    delete player;
}

// Main game loop
void NoTengoMuffins::update(float deltaTime, sf::RenderWindow*window) {
    InputManager::update();
    sf::Event event;
    while(window->pollEvent(event)){
        switch (event.type) {
            case (sf::Event::Closed):
            Game::i()->isRunning = false;
            break;
            case (sf::Event::KeyPressed):
            if(event.key.code == sf::Keyboard::Escape)
                // Exit the game like this
                Game::i()->isRunning = false;
            break;
            case (sf::Event::MouseButtonPressed):
            case (sf::Event::MouseButtonReleased) :
            _scenes[_scene]->updateButtons(event);

            default:
            break;

        }
    }
    _menu.update(deltaTime, window);
    // do shit
}

void NoTengoMuffins::draw(sf::RenderWindow*window) {
    //a e s t h e t i c s
    window->clear(sf::Color::Cyan);
    // draw shit
    _menu.draw(window);
    //map->draw(window);
    player->draw(window);
    window->display();
}
