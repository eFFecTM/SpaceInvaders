#include "SDLRocket.h"

SDLRocket::SDLRocket(int* windowWidth, int* windowHeight, SDL_Renderer* renderer, int x, int y)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    surface = SDL_LoadBMP("resources/PlayerRocket.bmpx");
    SDL_GetClipRect(surface, &rect);
    this->width = rect.w*4;
    this->height = rect.h*4;
    this->x = x-width/2;
    this->y = y-height;
    this->renderer = renderer;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

SDLRocket::~SDLRocket()
{
    std::cout << "Deleting Rocket" << std::endl;
}

void SDLRocket::render()
{
    SDL_Rect rect;
    rect.x = x * *windowWidth/800;
    rect.y = y * *windowHeight/600;
    rect.w = width * *windowWidth/800;
    rect.h = height * *windowHeight/600;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
