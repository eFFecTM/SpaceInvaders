#include "SDLPlayer.h"

SDLPlayer::SDLPlayer(int* windowWidth, int* windowHeight, SDL_Renderer* renderer, SDL_Surface* surface, int x, int y)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    SDL_GetClipRect(surface, &rect);
    this->width = rect.w*3;
    this->height = rect.h*3;
    this->x = x-width/2;
    this->y = y-height;
    this->renderer = renderer;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
}

SDLPlayer::~SDLPlayer()
{
    SDL_DestroyTexture(texture);
    std::cout << "Deleting Player" << std::endl;
}

void SDLPlayer::render()
{
    SDL_Rect rect;
    rect.x = x * *windowWidth/800;
    rect.y = y * *windowHeight/600;
    rect.w = width * *windowWidth/800;
    rect.h = height * *windowHeight/600;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}