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
        sf::Texture playerTexFace;
        sf::Texture playerTex;
        sf::Texture playerTex2;
        sf::Texture zombieTex;
        sf::Texture bulletTex;
        sf::Texture numberText;
        sf::Texture bulletTex2;
        std::vector<Player*> players;
        std::vector<Zombie*> zombies;
        std::vector<Bullet*> bullets;
        int scoreOffset = 64;
        Map* map;
        std::vector< std::vector<sf::Sprite> > scores = std::vector< std::vector<sf::Sprite> >(2,std::vector<sf::Sprite>(0));
        void calcScores();
        void split_score(std::vector<int>&, int);

};

#endif // PARTY_HPP
