#ifndef NOTENGOMUFFINS_HPP
#define NOTENGOMUFFINS_HPP
#include "Game.hpp"
#include "scene.hpp"
#include "menu.h"

class NoTengoMuffins : public Game {
    public:
        NoTengoMuffins();
        virtual ~NoTengoMuffins();

    private:
        GameScene::gameScene _scene;
        std::vector<Scene*> _scenes;
        Menu _menu;
        virtual void update(float deltaTime, sf::RenderWindow *window) final override;
        virtual void draw(sf::RenderWindow *window) final override;
};

#endif //NOTENGOMUFFINS_HPP
