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

    surface = SDL_LoadBMP("resources/Paused.bmpx");
    pausedTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    font = TTF_OpenFont("resources/impact.ttf",32);

    std::stringstream ss;
    ss << "PLAY GAME";
    surface = TTF_RenderText_Blended(font, ss.str().c_str(),{255,255,255});
    SDL_GetClipRect(surface, &menuOption1Rect);
    menuOption1T = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    surface = TTF_RenderText_Blended(font, ss.str().c_str(),{0,255,0});
    menuSelectedOption1T = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    ss.str(std::string()); // Clearing (reusing it)
    ss << "HIGHSCORES";
    surface = TTF_RenderText_Blended(font, ss.str().c_str(),{255,255,255});
    SDL_GetClipRect(surface, &menuOption2Rect);
    menuOption2T = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    surface = TTF_RenderText_Blended(font, ss.str().c_str(),{0,255,0});
    menuSelectedOption2T = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    ss.str(std::string()); // Clearing (reusing it)
    ss << "EXIT GAME";
    surface = TTF_RenderText_Blended(font, ss.str().c_str(),{255,255,255});
    SDL_GetClipRect(surface, &menuOption3Rect);
    menuOption3T = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    surface = TTF_RenderText_Blended(font, ss.str().c_str(),{0,255,0});
    menuSelectedOption3T = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    playerS = SDL_LoadBMP("resources/SpaceShip.bmpx");
    rocket1S = SDL_LoadBMP("resources/Rocket1.bmpx");
    rocket2S = SDL_LoadBMP("resources/Rocket2.bmpx");
    enemy1S = SDL_LoadBMP("resources/Enemy1.bmpx");
    enemy2S = SDL_LoadBMP("resources/Enemy2.bmpx");
    enemy3S = SDL_LoadBMP("resources/Enemy3.bmpx");
    enemy4S = SDL_LoadBMP("resources/Enemy4.bmpx");

    music = Mix_LoadMUS("resources/Mass_Effect_Uncharted_Worlds.mp3");
    Mix_VolumeMusic(MIX_MAX_VOLUME/8);
    Mix_FadeInMusic(music, -1,5000);

    rocket1 = Mix_LoadWAV("resources/rocket1.wav" );
    Mix_VolumeChunk(rocket1,MIX_MAX_VOLUME/4);

    rocket2 = Mix_LoadWAV("resources/rocket2.wav" );
    Mix_VolumeChunk(rocket2,MIX_MAX_VOLUME/4);
}

Enum SDLFactory::getEvent()
{
    SDL_Event event;
    Enum e = Default;

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
            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_P:
                        if(!event.key.repeat)
                        {
                            e = Pause;
                        }
                        break;
                    case SDL_SCANCODE_UP:
                        e = MenuUp;
                        break;
                    case SDL_SCANCODE_DOWN:
                        e = MenuDown;
                        break;
                    case SDL_SCANCODE_RETURN:
                        e = MenuEnter;
                        break;
                    default:
                        break;
                }
            default:
                break;
        }
    }

    const Uint8* currentKeystates = SDL_GetKeyboardState(NULL);
    if(currentKeystates[SDL_SCANCODE_LEFT])
    {
        if (currentKeystates[SDL_SCANCODE_SPACE])
            e = LeftShoot;
        else if(!currentKeystates[SDL_SCANCODE_RIGHT])
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

void SDLFactory::renderMenu(int selectedOption)
{
    SDL_Rect r = {100*windowWidth/800,0,menuRect.w*windowWidth/800,menuRect.h*windowHeight/600};
    SDL_RenderCopy(renderer, menuTexture, NULL, &r);

    switch(selectedOption)
    {
        case 1:
            r = {(400-menuOption1Rect.w/2)*windowWidth/800,350*windowHeight/600,menuOption1Rect.w*windowWidth/800,menuOption1Rect.h*windowHeight/600};
            SDL_RenderCopy(renderer, menuSelectedOption1T, NULL, &r);
            r = {(400-menuOption2Rect.w/2)*windowWidth/800,(400+menuOption1Rect.h)*windowHeight/600,menuOption2Rect.w*windowWidth/800,menuOption2Rect.h*windowHeight/600};
            SDL_RenderCopy(renderer, menuOption2T, NULL, &r);
            r = {(400-menuOption3Rect.w/2)*windowWidth/800,(450+2*menuOption1Rect.h)*windowHeight/600,menuOption3Rect.w*windowWidth/800,menuOption3Rect.h*windowHeight/600};
            SDL_RenderCopy(renderer, menuOption3T, NULL, &r);
            break;
        case 2:
            r = {(400-menuOption1Rect.w/2)*windowWidth/800,350*windowHeight/600,menuOption1Rect.w*windowWidth/800,menuOption1Rect.h*windowHeight/600};
            SDL_RenderCopy(renderer, menuOption1T, NULL, &r);
            r = {(400-menuOption2Rect.w/2)*windowWidth/800,(400+menuOption1Rect.h)*windowHeight/600,menuOption2Rect.w*windowWidth/800,menuOption2Rect.h*windowHeight/600};
            SDL_RenderCopy(renderer, menuSelectedOption2T, NULL, &r);
            r = {(400-menuOption3Rect.w/2)*windowWidth/800,(450+2*menuOption1Rect.h)*windowHeight/600,menuOption3Rect.w*windowWidth/800,menuOption3Rect.h*windowHeight/600};
            SDL_RenderCopy(renderer, menuOption3T, NULL, &r);
            break;
        case 3:
            r = {(400-menuOption1Rect.w/2)*windowWidth/800,350*windowHeight/600,menuOption1Rect.w*windowWidth/800,menuOption1Rect.h*windowHeight/600};
            SDL_RenderCopy(renderer, menuOption1T, NULL, &r);
            r = {(400-menuOption2Rect.w/2)*windowWidth/800,(400+menuOption1Rect.h)*windowHeight/600,menuOption2Rect.w*windowWidth/800,menuOption2Rect.h*windowHeight/600};
            SDL_RenderCopy(renderer, menuOption2T, NULL, &r);
            r = {(400-menuOption3Rect.w/2)*windowWidth/800,(450+2*menuOption1Rect.h)*windowHeight/600,menuOption3Rect.w*windowWidth/800,menuOption3Rect.h*windowHeight/600};
            SDL_RenderCopy(renderer, menuSelectedOption3T, NULL, &r);
            break;
        default:
            break;
    }
}

void SDLFactory::renderPaused()
{
    SDL_Rect r = {backgroundRect.x,backgroundRect.y,windowWidth,windowHeight};
    SDL_RenderCopy(renderer, pausedTexture, NULL, &r);
}

void SDLFactory::renderScore(int score)
{
    SDL_DestroyTexture(scoreTexture);
    std::stringstream ss;
    ss << "Score: " << score;
    surface = TTF_RenderText_Blended(font, ss.str().c_str(),{255,255,255});
    SDL_GetClipRect(surface, &scoreRect);
    scoreTexture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    SDL_Rect r = {0,0,scoreRect.w*windowWidth/800,scoreRect.h*windowHeight/600};
    SDL_RenderCopy(renderer, scoreTexture, NULL, &r);
}

void SDLFactory::renderLives(int lives)
{
    SDL_DestroyTexture(livesTexture);
    std::stringstream ss;
    ss << "Lives left: " << lives;
    surface = TTF_RenderText_Blended(font, ss.str().c_str(),{255,0,0});
    SDL_GetClipRect(surface, &livesRect);
    livesTexture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    SDL_Rect r = {(800-livesRect.w)*windowWidth/800,0,livesRect.w*windowWidth/800,livesRect.h*windowHeight/600};
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
