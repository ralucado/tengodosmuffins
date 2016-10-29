#ifndef GAME_HPP
#define GAME_HPP
#include "commons.hpp"

class Game {
    public:
        Game();
        virtual ~Game();
        static Game* i() { return Game::instance;}

        virtual void run();

        bool isRunning = true;
    protected:
        virtual void update(float deltaTime, sf::RenderWindow*window) = 0;
        virtual void draw(sf::RenderWindow*window) = 0;
    private:
        static Game* instance;
};

#endif //GAME_HPP
