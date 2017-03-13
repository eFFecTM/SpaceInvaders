#include "SDLPlayerShip.h"

SDLPlayerShip::SDLPlayerShip(SDL_Renderer* renderer, int x, int y, int width, int height) : PlayerShip(x, y, width, height)
{
    this->renderer = renderer;
    surface = SDL_LoadBMP("resources/SpaceShip.bmp");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void SDLPlayerShip::render()
{
    SDL_Rect rect;
    rect.x = x; rect.y = y; rect.w = width; rect.h = height;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
