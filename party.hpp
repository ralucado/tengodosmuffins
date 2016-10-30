#ifndef PARTY_HPP
#define PARTY_HPP
#include "commons.hpp"
#include "scene.hpp"
#include "InputManager.hpp"
#include "bullet.hpp"
class Player;
class Zombie;
class Map;

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
        void newShot(Player*id, sf::Vector2f dir);
        const std::vector<Player*>& getPlayers() const {return players;}
        const std::vector<Zombie*>& getZombies() const {return zombies;}
    private:
        sf::Image collisionMap;
        sf::Image backgroundMap;
        sf::Texture playerTex;
        sf::Texture zombieTex;
        sf::Texture bulletTex;
        std::vector<Player*> players;
        std::vector<Zombie*> zombies;
        std::vector<Bullet*> bullets;
        Map* map;

};

#endif // PARTY_HPP
