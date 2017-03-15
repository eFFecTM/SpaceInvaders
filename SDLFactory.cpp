#include "SDLFactory.h"
#include "SDLPlayerShip.h"
#include "SDLPlayerRocket.h"
#include <iostream>

using namespace std;

void SDLFactory::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    surface = SDL_LoadBMP("resources/Background.bmp");
    SDL_GetClipRect(surface, &rect);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

Event SDLFactory::getEvent()
{
    SDL_Event event;
    Event e = Default;

    SDL_PollEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
            e = Close;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_LEFT :
                    e = Left;
                    break;
                case SDLK_RIGHT :
                    e = Right;
                    break;
                case SDLK_SPACE :
                    e = Shoot;
                    break;
                default :
                    break;
            }
            break;
        case SDL_WINDOWEVENT:
            if(event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                windowWidth = event.window.data1;
                windowHeight = event.window.data2;
            }
            break;
        default:
            break;
    }

    return e;
}

void SDLFactory::renderBackground()
{
    SDL_RenderClear(renderer);
    SDL_Rect r;
    r.x = rect.x; r.y = rect.y; r.w = windowWidth; r.h = windowHeight;
    SDL_RenderCopy(renderer, texture, NULL, &r);
}

void SDLFactory::renderPresent()
{
    SDL_RenderPresent(renderer);
}

SDLFactory::~SDLFactory()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    SDL_Quit();
}

PlayerShip* SDLFactory::getPlayerShip()
{
    SDL_Rect rect;
    rect.x = 400;
    rect.y = 600;
    return new SDLPlayerShip(&windowWidth,&windowHeight,renderer,rect.x,rect.y);
}

PlayerRocket* SDLFactory::getPlayerRocket(int x, int y)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    return new SDLPlayerRocket(&windowWidth,&windowHeight,renderer,rect.x,rect.y);
}

