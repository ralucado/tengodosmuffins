#include "NoTengoMuffins.hpp"

NoTengoMuffins::NoTengoMuffins() {
    _state = GameState::menu;
    std::cout << "in menu" << std::endl;
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
            case (sf::Event::MouseMoved):
            case (sf::Event::MouseButtonPressed):
            switch(_state){
                case(GameState::menu):
                //std::cout << "still in menu" << std::endl;
                break;
                default:
                break;
            }

            default:
            break;

        }
    }

    // do shit
}

void NoTengoMuffins::draw(sf::RenderWindow*window) {
    //a e s t h e t i c s
    window->clear(sf::Color::Cyan);
    // draw shit
    window->display();
}
