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
    void moveEnemies();
    void collisionDetection();
    bool hasIntersection(Entity*,Entity*);

private:
    AbstractFactory *af;
    PlayerShip *playerShip;
    bool running = true;
    vector<Entity*> rockets;
    vector<Entity*> enemies;
    int ls,rs,us,bs;
    bool right = true;
};


#endif //SPACEINVADERS_GAME_H
