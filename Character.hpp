#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include "commons.hpp"

class Character : public sf::Sprite {
    public:
        Character(sf::Texture* tex, sf::Image* collisionMap);

        bool moveWithCollisions(sf::Vector2f dist);
        bool collides(sf::Vector2f dist);
        void setAnimState(unsigned int state);
        void updateTextureRect();
        unsigned int getAnimState();
        void updateAnimState(float deltaTime);

    protected:
        sf::Texture* t;

    private:
        sf::Image* collisionMap = nullptr;
        sf::Vector2f spriteSize = sf::Vector2f(128, 128);
        unsigned int numStates = 8;
        unsigned int numFrames = 1;
        float frameTime = 0.3f; //seconds
        // 0 <= currState < numStates
        unsigned int currState = 0;
        // 0 <= currFrame < numFrames
        unsigned int currFrame = 0;
        // currTime is time spent on this frame
        float currTime = 0.0f;
};

#endif // CHARACTER_HPP
