#include "NoTengoMuffins.hpp"

NoTengoMuffins::NoTengoMuffins() {
}

NoTengoMuffins::~NoTengoMuffins() {
}

// Main game loop
void NoTengoMuffins::update(float deltaTime, sf::RenderWindow*window) {
    // Exit the game like this
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        Game::i()->isRunning = false;
    }
    // do shit
}

void NoTengoMuffins::draw(sf::RenderWindow*window) {
    // draw shit
}
