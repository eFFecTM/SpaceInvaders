#ifndef SPACEINVADERS_SDLROCKET_H
#define SPACEINVADERS_SDLROCKET_H

#include "Rocket.h"
#include "SDLRender.h"
#include <SDL.h>
#include <sstream>
#include <string>

namespace NSSDL
{
    class SDLRocket : public NSGame::Rocket
    {
    public:
        SDLRocket(SDLRender *, SDL_Texture *, SDL_Rect *, int);

        virtual ~SDLRocket();

        int *getType();

        void render();

    private:
        SDL_Texture *texture = NULL;
        SDLRender *sdlRender = NULL;
    };
}

#endif //SPACEINVADERS_SDLROCKET_H
