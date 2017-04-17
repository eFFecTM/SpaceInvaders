/**
 * SDLEnemy class: More info at the header class
 */

#include "SDLEnemy.h"

namespace NSSDL
{
    SDLEnemy::SDLEnemy(SDLRender *render, SDL_Texture *texture, SDL_Rect *rect, int type)
    {
        this->width = rect->w * 3;
        this->height = rect->h * 3;
        this->x = rect->x - width / 2;
        this->y = rect->y - height / 2;
        this->texture = texture;
        this->type = type;
        sdlRender = render;
    }

    SDLEnemy::~SDLEnemy()
    {
        std::cout << "Deleting Enemy" << std::endl;
    }

    int *SDLEnemy::getType()
    {
        return &type;
    }

    void SDLEnemy::render()
    {
        sdlRender->render(texture, {x, y, width, height});
    }
}