#include "menu.h"
#include "NoTengoMuffins.hpp"

Menu::Menu() {
    _start.setPosition(5,5);
    _exit.setPosition(500,500);
    _start.turnOn();
    _exit.turnOn();
    _buttons.push_back(&_start);
    _buttons.push_back(&_exit);
}

void Menu::update(float deltaTime, sf::RenderWindow*window){
    //float dx = InputManager::action(InputAction::moveX0);
    //_buttons[0]->move(dx,0);
    //std::cout << dx << std::endl;
    for(unsigned int i = 0; i < _buttons.size(); ++i){
        _buttons[i]->update(window->mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(*window))));
    }
}

void Menu::draw(sf::RenderWindow* window){
    for(unsigned int i = 0; i < _buttons.size(); ++i){
        window->draw(*_buttons[i]);
    }
}

void Menu::updateButtons(sf::Event e){
    //std::cout << "update menu buttons" << std::endl;
    for(unsigned int i = 0; i < _buttons.size(); ++i){
        _buttons[i]->handleMouseEvent(e);
    }
    NoTengoMuffins* g = static_cast<NoTengoMuffins*>(Game::i());
    if (_start.getClicks() > 0){
        g->changeScene(GameScene::inGame);
    }
    else if(_exit.getClicks() > 0) g->isRunning = false;

}
