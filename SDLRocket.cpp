#include "SDLRocket.h"

SDLRocket::SDLRocket(int* windowWidth, int* windowHeight, SDL_Renderer* renderer, int x, int y, int type)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    std::stringstream ss;
    ss << "resources/Rocket" << type << ".bmpx";
    surface = SDL_LoadBMP(ss.str().c_str());
    SDL_GetClipRect(surface, &rect);
    this->width = rect.w*3;
    this->height = rect.h*3;
    this->x = x-width/2;
    this->y = y-height/2;
    this->renderer = renderer;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    this->type = type;
}

SDLRocket::~SDLRocket()
{
    SDL_DestroyTexture(texture);
    std::cout << "Deleting Rocket" << std::endl;
}

int* SDLRocket::getType()
{
    return &type;
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
