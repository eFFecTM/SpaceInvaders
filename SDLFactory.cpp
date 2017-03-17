#include "SDLFactory.h"
#include "SDLPlayer.h"
#include "SDLRocket.h"
#include "SDLEnemy.h"

SDLFactory::SDLFactory()
{
    SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1"); // Fixes debugging
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    surface = SDL_LoadBMP("resources/Background.bmpx");
    SDL_GetClipRect(surface, &backgroundRect);
    backGroundTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    font = TTF_OpenFont("resources/impact.ttf",48);
    renderScore(0);
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
    SDL_Rect r = {backgroundRect.x,backgroundRect.y,windowWidth,windowHeight};
    SDL_RenderCopy(renderer, backGroundTexture, NULL, &r);

}

void SDLFactory::renderScore(int score)
{
    std::stringstream ss;
    ss << "Score: " << score;
    surface = TTF_RenderText_Solid(font, ss.str().c_str(),{255,255,255});
    SDL_GetClipRect(surface, &textRect);
    textTexture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    SDL_Rect r = {0,600-textRect.h,textRect.w,textRect.h};
    SDL_RenderCopy(renderer, textTexture, NULL, &r);
}


void SDLFactory::renderPresent()
{
    SDL_RenderPresent(renderer);
}

SDLFactory::~SDLFactory()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(backGroundTexture);
    TTF_Quit();
    SDL_Quit();
}

Player* SDLFactory::getPlayer()
{
    SDL_Rect rect;
    rect.x = 400;
    rect.y = 600;
    return new SDLPlayer(&windowWidth,&windowHeight,renderer,rect.x,rect.y);
}

Rocket* SDLFactory::getRocket(int x, int y, int type)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    return new SDLRocket(&windowWidth,&windowHeight,renderer,rect.x,rect.y, type);
}

Enemy* SDLFactory::getEnemy(int x, int y, int type)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    return new SDLEnemy(&windowWidth,&windowHeight,renderer,rect.x,rect.y,type);
}
