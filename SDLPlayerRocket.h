#ifndef SPACEINVADERS_SDLPLAYERROCKET_H
#define SPACEINVADERS_SDLPLAYERROCKET_H

#include "PlayerRocket.h"
#include <SDL.h>

class SDLPlayerRocket : public PlayerRocket
{
public:
    SDLPlayerRocket(SDL_Renderer*,int,int,int,int);
    void render();
private:
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
    SDL_Renderer* renderer = NULL;
};


#endif //SPACEINVADERS_SDLPLAYERROCKET_H
