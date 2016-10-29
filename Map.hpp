#ifndef MAP_H
#define MAP_H
#include "commons.hpp"

class Map : public sf::Sprite {
    public:
        Map(sf::Image* image);
        
        void draw(sf::RenderWindow* window);
    private:
        sf::Texture t;
};

#endif // MAP_H
