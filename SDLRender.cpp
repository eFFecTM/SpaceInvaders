#include "SDLRender.h"

namespace NSSDL
{
    SDLRender::SDLRender(SDL_Renderer *renderer)
    {
        this->renderer = renderer;
        width = 800;
        height = 600;
    }

    void SDLRender::updateWindowSize(int width, int height)
    {
        this->width = width;
        this->height = height;
    }

    void SDLRender::render(SDL_Texture *texture, SDL_Rect rect)
    {
        SDL_Rect r = {rect.x * width / 800, rect.y * height / 600, rect.w * width / 800, rect.h * height / 600};
        SDL_RenderCopy(renderer, texture, NULL, &r);
    }
}