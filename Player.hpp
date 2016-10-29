#ifndef PLAYER_H
#define PLAYER_H
#include "Character.hpp"


class Player : public Character {
    public:
        Player();

        void update(float deltaTime);
};

#endif // PLAYER_H
