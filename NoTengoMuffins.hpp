#ifndef NOTENGOMUFFINS_HPP
#define NOTENGOMUFFINS_HPP
#include "Game.hpp"

class NoTengoMuffins : public Game {
    public:
        NoTengoMuffins();
        virtual ~NoTengoMuffins();

    private:
        virtual void update(float deltaTime, sf::RenderWindow *window) final override;
        virtual void draw(sf::RenderWindow *window) final override;
};

#endif //NOTENGOMUFFINS_HPP
