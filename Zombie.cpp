#include "Zombie.hpp"

Zombie::Zombie(sf::Image* collisionMap) : Character(collisionMap) {

}

void Zombie::update(float deltaTime)
{
    //nearest player
    //nearest seen player

    //set nearest alive player
        //nearest distance
    //set nearest seen alive player
        //raycasting between zombie an player

    //if nearest seen player != null
        //go towards nearest seen player

    // if nearest player != null
        //get last player checkpoint
        //get zombie last checkpoint
        //bfs between checkpoints
        //move towards nearest bfs checkpoint

    //if all null
        //move random between nearest checkpoints
}

