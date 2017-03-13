#ifndef SPACEINVADERS_PLAYERROCKET_H
#define SPACEINVADERS_PLAYERROCKET_H

#include "Player.h"

class PlayerRocket : public Player
{
public:
    PlayerRocket(int x,int y,int width,int height) : Player(x,y,width,height) {}
};

#endif //SPACEINVADERS_PLAYERROCKET_H
