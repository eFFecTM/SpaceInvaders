#include "SDLRocket.h"

namespace NSSDL
{
    SDLRocket::SDLRocket(SDLRender *render, SDL_Texture *texture, SDL_Rect *rect, int type)
    {
        this->width = rect->w * 3;
        this->height = rect->h * 3;
        this->x = rect->x - width / 2;
        this->y = rect->y - height / 2;
        this->texture = texture;
        this->type = type;
        sdlRender = render;
    }

    SDLRocket::~SDLRocket()
    {
        std::cout << "Deleting Rocket" << std::endl;
    }

    int *SDLRocket::getType()
    {
        return &type;
    }

    void SDLRocket::render()
    {
        sdlRender->render(texture, {x, y, width, height});
    }
}