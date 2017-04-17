/**
 * Header for Game class
 * Handles the game logic: players/enemies that shoot, movement of all entities,
 * collisiondetection between entities, finite state machine in what mode the player is
 * (menu, playing paused), separate dead player check and highscore management.
 */

#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include "AbstractFactory.h"

using namespace std;

namespace NSGame
{
    class Game
    {
    public:
        Game(AbstractFactory *);
        virtual ~Game(){};
        void start();
        bool handleEvent(Event);
        void shootPlayer();
        void shootEnemies();
        void movePlayer(Event);
        void moveRockets();
        void moveEnemies();
        void collisionDetection();
        bool hasIntersection(Entity *, Entity *);
        void menu();
        void playing();
        void paused();
        void addNewHighscore();
        void checkDead();
        void readHighscores();
        void writeHighscores();
    private:
        AbstractFactory *af;
        Player *player;
        bool running = true;
        vector<Rocket *> playerRockets;
        vector<Rocket *> enemyRockets;
        vector<Enemy *> enemies;
        int ls, rs, us, bs;
        bool right = true;
        Mode mode = Menu;
        bool isFirstPlaying = true, continuePlaying = false;
        int i = 0, counterSpeed = 25;
        int selectedOption = 1;
        vector<Score> highscore;
        string inputText = "";
    };
}

#endif //SPACEINVADERS_GAME_H
