#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

#include <vector>
#include "AbstractFactory.h"

using namespace std;

class Game
{
public:
    Game(AbstractFactory*);
    void start();
    bool handleEvent(Event);
    void movePlayerRockets();

private:
    AbstractFactory *af;
    PlayerShip *playerShip;
    bool running = true;
    vector<Entity*> entities;
    vector<Entity*> rockets;

};


#endif //SPACEINVADERS_GAME_H
