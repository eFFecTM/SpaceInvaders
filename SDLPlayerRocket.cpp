#include <iostream>
#include "SDLPlayerRocket.h"

SDLPlayerRocket::SDLPlayerRocket(SDL_Renderer* renderer,int x,int y,int width,int height) : PlayerRocket(x,y,width,height)
{
    std::cout << x << " - " << y << std::endl;
    this->renderer = renderer;
    surface = SDL_LoadBMP("resources/PlayerRocket.bmp");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void SDLPlayerRocket::render()
{
    SDL_Rect rect;

    rect.x = x; rect.y = y; rect.w = width; rect.h = height;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
