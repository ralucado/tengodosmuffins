#include "Game.hpp"

Game* Game::instance = nullptr;

Game::Game() {
    ASSERT(Game::instance == nullptr); //Two games created
    Game::instance = this;
    isRunning = true;

}

Game* Game::i() {
    return Game::instance;
}

Game::~Game() {
    isRunning = false;
    Game::instance = nullptr;
}

// Main game loop
void Game::run() {
    sf::Clock c;
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Tengo Dos Muffins!");
    window.setVerticalSyncEnabled(true);
    float oldTime = c.getElapsedTime().asSeconds();
    while (isRunning) {
        float time = c.getElapsedTime().asSeconds();
        float deltaTime = time-oldTime;
        oldTime = time;
        update(deltaTime, &window);
        draw( &window);
    }
    window.close();
}
