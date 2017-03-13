#ifndef SPACEINVADERS_PLAYER_H
#define SPACEINVADERS_PLAYER_H

#include "Entity.h"

class Player : public Entity
{
public:
    Player(int x, int y, int width, int height) : Entity(x,y,width,height) {}
};

#endif //SPACEINVADERS_PLAYER_H
