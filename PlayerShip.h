#ifndef SPACEINVADERS_PLAYERSHIP_H
#define SPACEINVADERS_PLAYERSHIP_H

#include "Player.h"

class PlayerShip : public Player
{
public:
    PlayerShip(int x, int y, int width, int height) : Player(x,y,width,height) {}
};

#endif //SPACEINVADERS_PLAYERSHIP_H
