#ifndef SPACEINVADERS_SDLFACTORY_H
#define SPACEINVADERS_SDLFACTORY_H

#include "AbstractFactory.h"
#include <SDL.h>

class SDLFactory : public AbstractFactory
{
public:
    virtual ~SDLFactory();
    PlayerShip* getPlayerShip();
    void init();
    Event getEvent();
    void renderBackground();
    void renderPresent();
private:
    SDL_Window* window = NULL; // Good practice
    SDL_Renderer* renderer = NULL;
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
};


#endif //SPACEINVADERS_SDLFACTORY_H
