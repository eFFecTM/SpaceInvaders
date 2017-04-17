/**
 * Header for SDLEnemy class
 * Contains Texture of enemy, calls SDLRender function to render it
 */

#ifndef SPACEINVADERS_SDLENEMY_H
#define SPACEINVADERS_SDLENEMY_H

#include "Enemy.h"
#include "SDLRender.h"
#include <SDL.h>

namespace NSSDL
{
    class SDLEnemy : public NSGame::Enemy
    {
    public:
        SDLEnemy(SDLRender *, SDL_Texture *, SDL_Rect *, int);
        virtual ~SDLEnemy();
        int *getType();
        void render();
    private:
        SDL_Texture *texture = NULL;
        SDLRender *sdlRender = NULL;
    };
}

#endif //SPACEINVADERS_SDLENEMY_H
