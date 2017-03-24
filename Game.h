#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

#include <vector>
#include <stdlib.h>
#include <time.h>
#include "AbstractFactory.h"

using namespace std;

class Game
{
public:
    Game(AbstractFactory*);
    void start();
    bool handleEvent(Event);
    void shootPlayer();
    void shootEnemies();
    void movePlayer(Event);
    void moveRockets();
    void moveEnemies();
    void collisionDetection();
    bool hasIntersection(Entity*,Entity*);
    void menu();
    void playing();
    void paused();
    void showHighscores();
    void addNewHighscore();
    void checkDead();

private:
    AbstractFactory *af;
    Player *player;
    bool running = true;
    vector<Rocket*> playerRockets;
    vector<Rocket*> enemyRockets;
    vector<Enemy*> enemies;
    int ls,rs,us,bs;
    bool right = true;
    Mode mode = Menu;
    bool isFirstPlaying = true, continuePlaying = false;
    int i=0;
    int selectedOption = 1;


};


#endif //SPACEINVADERS_GAME_H
