#ifndef SPACEINVADERS_SDLPLAYERSHIP_H
#define SPACEINVADERS_SDLPLAYERSHIP_H

#include "PlayerShip.h"
#include <SDL.h>

class SDLPlayerShip : public PlayerShip
{
public:
    SDLPlayerShip(SDL_Renderer*,int,int,int,int);
    void render();
private:
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
    SDL_Renderer* renderer = NULL;
};


#endif //SPACEINVADERS_SDLPLAYERSHIP_H
