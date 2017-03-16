//
// Created by Jan on 16/03/2017.
//

#ifndef SPACEINVADERS_SDLENEMY_H
#define SPACEINVADERS_SDLENEMY_H

#include "Enemy.h"
#include <SDL.h>
#include <sstream>
#include <string>
#include <iostream>

class SDLEnemy : public Enemy
{
public:
    SDLEnemy(int*,int*,SDL_Renderer*,int,int,int);
    virtual ~SDLEnemy();
    void render();
private:
    int *windowWidth, *windowHeight;
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Rect rect;
};

#endif //SPACEINVADERS_SDLENEMY_H
