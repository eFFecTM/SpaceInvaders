/**
 * SDLPlayer class: More info at the header class
 */

#include "SDLPlayer.h"

namespace NSSDL
{
    SDLPlayer::SDLPlayer(SDLRender *render, SDL_Texture *texture, SDL_Rect *rect)
    {
        this->width = rect->w * 3;
        this->height = rect->h * 3;
        this->x = rect->x - width / 2;
        this->y = rect->y - height;
        this->texture = texture;
        sdlRender = render;
    }

    SDLPlayer::~SDLPlayer()
    {
        std::cout << "Deleting Player" << std::endl;
    }

    void SDLPlayer::render()
    {
        sdlRender->render(texture, {x, y, width, height});
    }
}