#ifndef SPACEINVADERS_ABSTRACTFACTORY_H
#define SPACEINVADERS_ABSTRACTFACTORY_H

#include "PlayerShip.h"
#include "Event.h"

class AbstractFactory
{
public:
    virtual PlayerShip* getPlayerShip() = 0; // Maak abstract
    virtual void init() = 0;
    virtual Event getEvent() = 0;
    virtual void renderBackground() = 0;
    virtual void renderPresent() = 0;
};

#endif //SPACEINVADERS_ABSTRACTFACTORY_H
