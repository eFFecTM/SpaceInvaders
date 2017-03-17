#ifndef SPACEINVADERS_SDLPLAYERROCKET_H
#define SPACEINVADERS_SDLPLAYERROCKET_H

#include "Rocket.h"
#include <SDL.h>

class SDLRocket : public Rocket
{
public:
    SDLRocket(int*,int*,SDL_Renderer*,int,int);
    virtual ~SDLRocket();
    void render();
private:
    int *windowWidth, *windowHeight;
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Rect rect;
};

#endif //SPACEINVADERS_SDLPLAYERROCKET_H
