#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

#include "AbstractFactory.h"

class Game
{
public:
    Game(AbstractFactory*);
    void start();
    bool handleEvent(Event);

private:
    AbstractFactory *af;
    PlayerShip *playerShip;
    bool running = true;


};


#endif //SPACEINVADERS_GAME_H
