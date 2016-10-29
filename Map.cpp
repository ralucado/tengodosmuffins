#include "Map.hpp"

Map::Map(sf::Image* mapImg) {
    t.loadFromImage(*mapImg);
    setTexture(t);
    setTextureRect(sf::IntRect(0,0, 1920, 1080));
}

void Map::draw(sf::RenderWindow* window) {
    window->draw(*this);
}
