#ifndef SPACEINVADERS_SDLPLAYERSHIP_H
#define SPACEINVADERS_SDLPLAYERSHIP_H

#include "PlayerShip.h"
#include <SDL.h>

class SDLPlayerShip : public PlayerShip
{
public:
    SDLPlayerShip(int*,int*,SDL_Renderer*,int,int);
    void render();
private:
    int *windowWidth, *windowHeight;
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Rect rect;
};

#endif //SPACEINVADERS_SDLPLAYERSHIP_H
