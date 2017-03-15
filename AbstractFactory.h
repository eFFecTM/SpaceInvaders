#ifndef SPACEINVADERS_ABSTRACTFACTORY_H
#define SPACEINVADERS_ABSTRACTFACTORY_H

#include "PlayerRocket.h"
#include "PlayerShip.h"
#include "Event.h"

class AbstractFactory
{
public:
    virtual PlayerShip* getPlayerShip() = 0; // Maak abstract
    virtual PlayerRocket* getPlayerRocket(int,int) = 0;
    virtual void init() = 0;
    virtual Event getEvent() = 0;
    virtual void renderBackground() = 0;
    virtual void renderPresent() = 0;
};

#endif //SPACEINVADERS_ABSTRACTFACTORY_H
