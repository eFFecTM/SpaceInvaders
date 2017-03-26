#ifndef SPACEINVADERS_ABSTRACTFACTORY_H
#define SPACEINVADERS_ABSTRACTFACTORY_H

#include "Rocket.h"
#include "Player.h"
#include "Enemy.h"
#include "Enum.h"
#include <vector>

class AbstractFactory
{
public:
    AbstractFactory(){};
    virtual Player* getPlayer() = 0; // Maak abstract
    virtual Rocket* getRocket(int,int,int) = 0;
    virtual Enemy* getEnemy(int,int,int) = 0;
    virtual Event getEvent() = 0;
    virtual void renderBackground() = 0;
    virtual void renderMenu(int) = 0;
    virtual void renderPaused() = 0;
    virtual void renderScore(int) = 0;
    virtual void renderLives(int) = 0;
    virtual void renderPresent() = 0;
    virtual void startTimer() = 0;
    virtual int getTickDifference() = 0;
    virtual void addDelay(int) = 0;
    virtual void playSoundEffect(int) = 0;
    virtual void makeHighscore(std::vector<Score>*) = 0;
    virtual void renderHighscore(int) = 0;
    virtual void renderGameOver() = 0;
    virtual std::string getInputText() = 0;
    virtual void enableTextInput() = 0;
    virtual void renderNewHighscore() = 0;
};

#endif //SPACEINVADERS_ABSTRACTFACTORY_H
