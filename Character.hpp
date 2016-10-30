#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include "commons.hpp"

class Party;
class Character : public sf::Sprite {
    public:
        Character(Party* p, sf::Texture* tex, sf::Image* collisionMap, int nStates, int nFrames);

        bool moveWithCollisions(sf::Vector2f dist);
        bool collides(sf::Vector2f dist);
        void setAnimState(unsigned int state);
        void updateTextureRect();
        unsigned int getAnimState();
        void updateAnimState(float deltaTime);

    protected:
        bool checkPixel(sf::Vector2f v, sf::Color c);
        sf::Texture* t;
        Party* scene;
        float spriteSize = 128;

    private:
        sf::Image* collisionMap = nullptr;
        unsigned int numStates;
        unsigned int numFrames;
        float frameTime = 0.1f; //seconds
        // 0 <= currState < numStates
        unsigned int currState = 0;
        // 0 <= currFrame < numFrames
        unsigned int currFrame = 0;
        // currTime is time spent on this frame
        float currTime = 0.0f;
};

#endif // CHARACTER_HPP
