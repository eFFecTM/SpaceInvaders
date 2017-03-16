#ifndef SPACEINVADERS_SDLFACTORY_H
#define SPACEINVADERS_SDLFACTORY_H

#include "AbstractFactory.h"
#include <SDL.h>

class SDLFactory : public AbstractFactory
{
public:
    virtual ~SDLFactory();
    PlayerShip* getPlayerShip();
    PlayerRocket* getPlayerRocket(int,int);
    Enemy* getEnemy(int,int,int);
    void init();
    Event getEvent();
    void renderBackground();
    void renderPresent();
private:
    SDL_Window* window = NULL; // Good practice
    SDL_Renderer* renderer = NULL;
    SDL_Surface* surface = NULL;
    SDL_Rect rect;
    SDL_Texture* texture = NULL;
    int windowWidth = 800, windowHeight = 600;
};

#endif //SPACEINVADERS_SDLFACTORY_H
