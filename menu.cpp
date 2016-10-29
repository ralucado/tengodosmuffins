#include "menu.h"

Menu::Menu(){
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
    if (_start.getClicks()>0){

    }
}

void Menu::draw(sf::RenderWindow* window){
    for(unsigned int i = 0; i < _buttons.size(); ++i){
        window->draw(*_buttons[i]);
//        sf::RectangleShape r(sf::Vector2f(_buttons[i]->getGlobalBounds().width,_buttons[i]->getGlobalBounds().height));
//        r.setPosition(_buttons[i]->getGlobalBounds().left, _buttons[i]->getGlobalBounds().top);
//        r.setOutlineThickness(1);
//        r.setOutlineColor(sf::Color::Red);
//        r.setFillColor(sf::Color::Transparent);
//        window->draw(r);
//        sf::RectangleShape z(sf::Vector2f(5,5));
//        z.setPosition(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
//        z.setFillColor(sf::Color::Blue);
//        window->draw(z);
    }
}

void Menu::updateButtons(sf::Event e){
    //std::cout << "update menu buttons" << std::endl;
    for(unsigned int i = 0; i < _buttons.size(); ++i){
        _buttons[i]->handleMouseEvent(e);
    }
}
