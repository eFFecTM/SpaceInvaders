#ifndef SPACEINVADERS_SDLPLAYER_H
#define SPACEINVADERS_SDLPLAYER_H

#include "Player.h"
#include <SDL.h>

class SDLPlayer : public Player
{
public:
    SDLPlayer(int*,int*,SDL_Renderer*,SDL_Surface*,int,int);
    virtual ~SDLPlayer();
    void render();
private:
    int *windowWidth, *windowHeight;
    //SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Rect rect;
};

#endif //SPACEINVADERS_SDLPLAYER_H
