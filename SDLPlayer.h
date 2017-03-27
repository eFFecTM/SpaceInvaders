#ifndef SPACEINVADERS_SDLPLAYER_H
#define SPACEINVADERS_SDLPLAYER_H

#include "Player.h"
#include "SDLRender.h"
#include <SDL.h>

namespace NSSDL
{
    class SDLPlayer : public NSGame::Player
    {
    public:
        SDLPlayer(SDLRender *, SDL_Texture *, SDL_Rect *);

        virtual ~SDLPlayer();

        void render();

    private:
        SDL_Texture *texture = NULL;
        SDLRender *sdlRender = NULL;
    };
}
#endif //SPACEINVADERS_SDLPLAYER_H
