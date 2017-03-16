#ifndef SPACEINVADERS_SDLPLAYERROCKET_H
#define SPACEINVADERS_SDLPLAYERROCKET_H

#include "PlayerRocket.h"
#include <SDL.h>

class SDLPlayerRocket : public PlayerRocket
{
public:
    SDLPlayerRocket(int*,int*,SDL_Renderer*,int,int);
    virtual ~SDLPlayerRocket();
    void render();
private:
    int *windowWidth, *windowHeight;
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Rect rect;
};

#endif //SPACEINVADERS_SDLPLAYERROCKET_H
