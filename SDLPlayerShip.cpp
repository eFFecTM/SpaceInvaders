#include "SDLPlayerShip.h"

SDLPlayerShip::SDLPlayerShip(int* windowWidth, int* windowHeight, SDL_Renderer* renderer, int x, int y)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    surface = SDL_LoadBMP("resources/SpaceShip.bmp");
    SDL_GetClipRect(surface, &rect);
    this->width = rect.w*4;
    this->height = rect.h*4;
    this->x = x-width/2;
    this->y = y-height;
    this->renderer = renderer;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void SDLPlayerShip::render()
{
    SDL_Rect rect;
    rect.x = x * *windowWidth/800;
    rect.y = y * *windowHeight/600;
    rect.w = width * *windowWidth/800;
    rect.h = height * *windowHeight/600;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
