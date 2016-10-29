#ifndef PARTY_HPP
#define PARTY_HPP
#include "commons.hpp"
#include "scene.hpp"
#include "InputManager.hpp"
#include "Map.hpp"
#include "Player.hpp"

class Party : public Scene{
    public:
        Party();
        ~Party();
        Party(const Party& m) = delete;
        Party(const Party&& m) = delete;
        Party& operator=(Party& m) = delete;
        Party& operator=(Party&& m) = delete;
        void update(float deltaTime, sf::RenderWindow *window) final override;
        void draw(sf::RenderWindow *window) final override;
        void updateButtons(sf::Event e) final override;
    private:
        sf::Image collisionMap;
        Player* player1 = nullptr;
        Player* player2 = nullptr;
        Map* map;

};

#endif // PARTY_HPP
