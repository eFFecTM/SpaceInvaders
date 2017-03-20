#ifndef SPACEINVADERS_SDLPLAYERROCKET_H
#define SPACEINVADERS_SDLPLAYERROCKET_H

#include "Rocket.h"
#include <SDL.h>
#include <sstream>
#include <string>

class SDLRocket : public Rocket
{
public:
    SDLRocket(int*,int*,SDL_Renderer*,SDL_Surface*,int,int,int);
    virtual ~SDLRocket();
    int* getType();
    void render();
private:
    int *windowWidth, *windowHeight;
    //SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Rect rect;
};

#endif //SPACEINVADERS_SDLPLAYERROCKET_H
