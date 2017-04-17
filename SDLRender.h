/**
 * Header for SDLRender class
 * Generalized class for rendering textures on screen
 */

#ifndef SPACEINVADERS_SDLRENDER_H
#define SPACEINVADERS_SDLRENDER_H

#include <SDL.h>

namespace NSSDL
{
    class SDLRender
    {
    public:
        SDLRender(SDL_Renderer *);
        virtual ~SDLRender(){};
        void updateWindowSize(int, int);
        void render(SDL_Texture *, SDL_Rect);
    private:
        SDL_Renderer *renderer;
        int width, height;
    };
}

#endif //SPACEINVADERS_SDLRENDER_H
