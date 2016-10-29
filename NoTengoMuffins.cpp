#include "NoTengoMuffins.hpp"

NoTengoMuffins::NoTengoMuffins() {
}

NoTengoMuffins::~NoTengoMuffins() {
}

// Main game loop
void NoTengoMuffins::update(float deltaTime, sf::RenderWindow*window) {
    sf::Event event;
    while(window->pollEvent(event)){
        switch (event.type) {
            case (sf::Event::Closed):
            window->close();
            break;
            case (sf::Event::KeyPressed):
            if(event.key.code == sf::Keyboard::Escape)
                window->close();
            break;
            default:
            break;

        }
    }
    // Exit the game like this
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        Game::i()->isRunning = false;
    }
    // do shit
}

void NoTengoMuffins::draw(sf::RenderWindow*window) {
    // draw shit
}
