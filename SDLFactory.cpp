#include "SDLFactory.h"
#include "SDLPlayer.h"
#include "SDLRocket.h"
#include "SDLEnemy.h"

SDLFactory::SDLFactory()
{
    SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1"); // Fixes debugging
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);

    window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    menuS = SDL_LoadBMP("resources/Menu.bmpx");
    SDL_GetClipRect(menuS, &menuRect);
    menuTexture = SDL_CreateTextureFromSurface(renderer, menuS);
    SDL_FreeSurface(menuS);

    backgroundS = SDL_LoadBMP("resources/Background.bmpx");
    SDL_GetClipRect(backgroundS, &backgroundRect);
    backGroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundS);
    SDL_FreeSurface(backgroundS);

    playerS = SDL_LoadBMP("resources/SpaceShip.bmpx");
    rocket1S = SDL_LoadBMP("resources/Rocket1.bmpx");
    rocket2S = SDL_LoadBMP("resources/Rocket2.bmpx");
    enemy1S = SDL_LoadBMP("resources/Enemy1.bmpx");
    enemy2S = SDL_LoadBMP("resources/Enemy2.bmpx");
    enemy3S = SDL_LoadBMP("resources/Enemy3.bmpx");
    enemy4S = SDL_LoadBMP("resources/Enemy4.bmpx");

    font = TTF_OpenFont("resources/impact.ttf",32);

    music = Mix_LoadMUS("resources/Mass_Effect_Uncharted_Worlds.mp3");
    Mix_VolumeMusic(MIX_MAX_VOLUME/8);
    Mix_FadeInMusic(music, -1,5000);

    rocket1 = Mix_LoadWAV("resources/rocket1.wav" );
    Mix_VolumeChunk(rocket1,MIX_MAX_VOLUME/4);

    rocket2 = Mix_LoadWAV("resources/rocket2.wav" );
    Mix_VolumeChunk(rocket2,MIX_MAX_VOLUME/4);
}

Event SDLFactory::getEvent()
{
    SDL_Event event;
    Event e = Default;

    while(SDL_PollEvent(&event) != 0) // handle all events in queue first!
    {
        switch(event.type)
        {
            case SDL_QUIT:
                e = Close;
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
    }

    const Uint8* currentKeystates = SDL_GetKeyboardState(NULL);
    if(currentKeystates[SDL_SCANCODE_P])
        e = Pause;
    else if(currentKeystates[SDL_SCANCODE_UP])
        e = MenuUp;
    else if(currentKeystates[SDL_SCANCODE_DOWN])
        e = MenuDown;
    else if(currentKeystates[SDL_SCANCODE_LEFT])
    {
        if (currentKeystates[SDL_SCANCODE_SPACE])
            e = LeftShoot;
        else
            e = Left;
    }
    else if(currentKeystates[SDL_SCANCODE_RIGHT])
    {
        if (currentKeystates[SDL_SCANCODE_SPACE])
            e = RightShoot;
        else
            e = Right;
    }
    else if(currentKeystates[SDL_SCANCODE_SPACE])
        e = Shoot;

    return e;
}

void SDLFactory::renderBackground()
{
    SDL_RenderClear(renderer);
    SDL_Rect r = {backgroundRect.x,backgroundRect.y,windowWidth,windowHeight};
    SDL_RenderCopy(renderer, backGroundTexture, NULL, &r);
}

void SDLFactory::renderMenu()
{
    SDL_Rect r = {100*windowWidth/800,0,menuRect.w*windowWidth/800,menuRect.h*windowHeight/600};
    SDL_RenderCopy(renderer, menuTexture, NULL, &r);
}

void SDLFactory::renderScore(int score)
{
    SDL_DestroyTexture(scoreTexture);
    std::stringstream ss;
    ss << "Score: " << score;
    scoreS = TTF_RenderText_Blended(font, ss.str().c_str(),{255,255,255});
    SDL_GetClipRect(scoreS, &scoreRect);
    scoreTexture = SDL_CreateTextureFromSurface(renderer,scoreS);
    SDL_FreeSurface(scoreS);
    SDL_Rect r = {0,0,scoreRect.w*windowWidth/800,scoreRect.h*windowHeight/600};
    SDL_RenderCopy(renderer, scoreTexture, NULL, &r);
}

void SDLFactory::renderLives(int lives)
{
    SDL_DestroyTexture(livesTexture);
    std::stringstream ss;
    ss << "Lives left: " << lives;
    livesS = TTF_RenderText_Blended(font, ss.str().c_str(),{255,255,255});
    SDL_GetClipRect(livesS, &livesRect);
    livesTexture = SDL_CreateTextureFromSurface(renderer,livesS);
    SDL_FreeSurface(livesS);
    SDL_Rect r = {(800-livesRect.w)*windowHeight/800,0,livesRect.w*windowWidth/800,livesRect.h*windowHeight/600};
    SDL_RenderCopy(renderer, livesTexture, NULL, &r);
}


void SDLFactory::renderPresent()
{
    SDL_RenderPresent(renderer);
}

SDLFactory::~SDLFactory()
{
    Mix_FreeChunk(rocket1);
    Mix_FreeChunk(rocket2);
    Mix_FreeMusic(music);
    SDL_DestroyTexture(livesTexture);
    SDL_DestroyTexture(scoreTexture);
    SDL_DestroyTexture(backGroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

Player* SDLFactory::getPlayer()
{
    SDL_Rect rect;
    rect.x = 400;
    rect.y = 600;
    return new SDLPlayer(&windowWidth,&windowHeight,renderer,playerS,rect.x,rect.y);

}

Rocket* SDLFactory::getRocket(int x, int y, int type)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    if(type == 1)
        return new SDLRocket(&windowWidth,&windowHeight,renderer,rocket1S, rect.x,rect.y, type);
    else if(type == 2)
        return new SDLRocket(&windowWidth,&windowHeight,renderer,rocket2S, rect.x,rect.y, type);
    else
        return 0;
}

Enemy* SDLFactory::getEnemy(int x, int y, int type)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;

    switch(type)
    {
        case 1:
            return new SDLEnemy(&windowWidth,&windowHeight,renderer,enemy1S,rect.x,rect.y,type);
        case 2:
            return new SDLEnemy(&windowWidth,&windowHeight,renderer,enemy2S,rect.x,rect.y,type);
        case 3:
            return new SDLEnemy(&windowWidth,&windowHeight,renderer,enemy3S,rect.x,rect.y,type);
        case 4:
            return new SDLEnemy(&windowWidth,&windowHeight,renderer,enemy4S,rect.x,rect.y,type);
        default:
            return 0;
    }
}

void SDLFactory::startTimer()
{
    startTicks = SDL_GetTicks();
}

int SDLFactory::getTickDifference()
{
    return SDL_GetTicks() - startTicks;
}

void SDLFactory::addDelay(int time)
{
    SDL_Delay((Uint32) time); //Wait remaining time
}

void SDLFactory::playSoundEffect(int type)
{
    if(type == 1)
        Mix_PlayChannel(-1,rocket1,0);
    else
        Mix_PlayChannel(-1,rocket2,0);
}
