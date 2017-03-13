#include "SDLFactory.h"
#include "SDLPlayerShip.h"
#include "SDLPlayerRocket.h"
#include <iostream>

using namespace std;

void SDLFactory::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    surface = SDL_LoadBMP("resources/Background.bmp");
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
        default:
            break;
    }

    return e;
}

void SDLFactory::renderBackground()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
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

Entity* SDLFactory::getPlayerShip()
{
    SDL_Rect rect;
    rect.x = 340;
    rect.y = 520;
    rect.w = 80;
    rect.h = 80;

    return new SDLPlayerShip(renderer,rect.x,rect.y,rect.w,rect.h);
}

Entity* SDLFactory::getPlayerRocket(int x, int y)
{
    SDL_Rect rect;
    rect.x = x-1;
    rect.y = y;
    rect.w = 3;
    rect.h = 13;
    cout << x << " " << y << endl;

    return new SDLPlayerRocket(renderer,rect.x,rect.y,rect.w,rect.h);
}
