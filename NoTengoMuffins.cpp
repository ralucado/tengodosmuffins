#include "NoTengoMuffins.hpp"
#include "InputManager.hpp"
#include "Map.hpp"

NoTengoMuffins::NoTengoMuffins() {

    //std::cout << "what " << std::endl;

    _scene = GameScene::inGame;
    _scenes = std::vector<Scene*>(SCENE_NUM);
    //std::cout << "in menu" << std::endl;
    _scenes[GameScene::menu] = &_menu;
    _scenes[GameScene::inGame] = &_party;

}

NoTengoMuffins::~NoTengoMuffins() {

}

// Main game loop
void NoTengoMuffins::update(float deltaTime, sf::RenderWindow*window) {
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
    _scenes[_scene]->update(deltaTime,window);

    // do shit
}

void NoTengoMuffins::draw(sf::RenderWindow*window) {
    //a e s t h e t i c s
    window->clear(sf::Color::Cyan);
    // draw shit
    _scenes[_scene]->draw(window);
    window->display();
}
