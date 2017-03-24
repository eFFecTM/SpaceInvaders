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

    menuT = createTextureFromImage("resources/Menu.bmpx",&menuR);
    backgroundT = createTextureFromImage("resources/Background.bmpx",&backgroundR);
    pausedT = createTextureFromImage("resources/Paused.bmpx",&backgroundR); // Same size as background rect, so reusing it

    font = TTF_OpenFont("resources/impact.ttf",32);

    menuOption1T = createTextureFromText("PLAY GAME",{255,255,255},&menuOption1R);
    menuSelectedOption1T = createTextureFromText("PLAY GAME",{0,255,0},&menuOption1R);

    menuOption2T = createTextureFromText("HIGHSCORES",{255,255,255},&menuOption2R);
    menuSelectedOption2T = createTextureFromText("HIGHSCORES",{0,255,0},&menuOption2R);

    menuOption3T = createTextureFromText("EXIT GAME",{255,255,255},&menuOption3R);
    menuSelectedOption3T = createTextureFromText("EXIT GAME",{0,255,0},&menuOption3R);

    playerT = createTextureFromImage("resources/SpaceShip.bmpx",&playerR);
    rocket1T = createTextureFromImage("resources/Rocket1.bmpx",&rocket1R);
    rocket2T = createTextureFromImage("resources/Rocket2.bmpx",&rocket2R);
    enemy1T = createTextureFromImage("resources/Enemy1.bmpx",&enemy1R);
    enemy2T = createTextureFromImage("resources/Enemy2.bmpx",&enemy2R);
    enemy3T = createTextureFromImage("resources/Enemy3.bmpx",&enemy3R);
    enemy4T = createTextureFromImage("resources/Enemy4.bmpx",&enemy4R);

//    music = Mix_LoadMUS("resources/Mass_Effect_Uncharted_Worlds.mp3");
    music = Mix_LoadMUS("resources/Icarus_8bit.mp3");
    Mix_VolumeMusic(MIX_MAX_VOLUME/8);
    Mix_FadeInMusic(music, -1,5000);

    rocket1M = Mix_LoadWAV("resources/rocket1.wav");
    Mix_VolumeChunk(rocket1M,MIX_MAX_VOLUME/4);

    rocket2M = Mix_LoadWAV("resources/rocket2.wav");
    Mix_VolumeChunk(rocket2M,MIX_MAX_VOLUME/4);

    sdlRender = new SDLRender(renderer);
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
                    sdlRender->updateWindowSize(event.window.data1,event.window.data2);
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

SDL_Texture* SDLFactory::createTextureFromImage(std::string path, SDL_Rect* rect )
{
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    SDL_GetClipRect(surface, rect);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

SDL_Texture* SDLFactory::createTextureFromText(std::string text, SDL_Color color ,SDL_Rect* rect)
{
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(),color);
    SDL_GetClipRect(surface, rect);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    return texture;
}

void SDLFactory::renderBackground()
{
    SDL_RenderClear(renderer);
    sdlRender->render(backgroundT,backgroundR);
}

void SDLFactory::renderMenu(int selectedOption)
{
    SDL_Rect rect = {100,0,menuR.w,menuR.h};
    sdlRender->render(menuT,rect);

    switch(selectedOption)
    {
        case 1:
            sdlRender->render(menuSelectedOption1T,{400-menuOption1R.w/2,350,menuOption1R.w,menuOption1R.h});
            sdlRender->render(menuOption2T,{400-menuOption2R.w/2,400+menuOption1R.h,menuOption2R.w,menuOption2R.h});
            sdlRender->render(menuOption3T,{400-menuOption3R.w/2,450+2*menuOption1R.h,menuOption3R.w,menuOption3R.h});
            break;
        case 2:
            sdlRender->render(menuOption1T,{400-menuOption1R.w/2,350,menuOption1R.w,menuOption1R.h});
            sdlRender->render(menuSelectedOption2T,{400-menuOption2R.w/2,400+menuOption1R.h,menuOption2R.w,menuOption2R.h});
            sdlRender->render(menuOption3T,{400-menuOption3R.w/2,450+2*menuOption1R.h,menuOption3R.w,menuOption3R.h});
            break;
        case 3:
            sdlRender->render(menuOption1T,{400-menuOption1R.w/2,350,menuOption1R.w,menuOption1R.h});
            sdlRender->render(menuOption2T,{400-menuOption2R.w/2,400+menuOption1R.h,menuOption2R.w,menuOption2R.h});
            sdlRender->render(menuSelectedOption3T,{400-menuOption3R.w/2,450+2*menuOption1R.h,menuOption3R.w,menuOption3R.h});
            break;
        default:
            break;
    }
}

void SDLFactory::renderPaused()
{
    sdlRender->render(pausedT,backgroundR);
}

void SDLFactory::renderScore(int score)
{
    SDL_DestroyTexture(scoreT);
    std::stringstream ss;
    ss << "Score: " << score;
    scoreT = createTextureFromText(ss.str().c_str(),{255,255,255},&scoreR);
    sdlRender->render(scoreT,scoreR);
}

void SDLFactory::renderLives(int lives)
{
    SDL_DestroyTexture(livesT);
    std::stringstream ss;
    ss << "Lives left: " << lives;
    livesT = createTextureFromText(ss.str().c_str(),{255,0,0},&livesR);
    sdlRender->render(livesT,{800-livesR.w,0,livesR.w,livesR.h});
}

void SDLFactory::renderPresent()
{
    SDL_RenderPresent(renderer);
}

SDLFactory::~SDLFactory()
{
    Mix_FreeChunk(rocket1M);
    Mix_FreeChunk(rocket2M);
    Mix_FreeMusic(music);
    SDL_DestroyTexture(livesT);
    SDL_DestroyTexture(scoreT);
    SDL_DestroyTexture(backgroundT);
    SDL_DestroyTexture(menuT);
    SDL_DestroyTexture(menuOption1T);
    SDL_DestroyTexture(menuOption2T);
    SDL_DestroyTexture(menuOption3T);
    SDL_DestroyTexture(menuSelectedOption1T);
    SDL_DestroyTexture(menuSelectedOption2T);
    SDL_DestroyTexture(menuSelectedOption3T);
    SDL_DestroyTexture(playerT);
    SDL_DestroyTexture(rocket1T);
    SDL_DestroyTexture(rocket2T);
    SDL_DestroyTexture(enemy1T);
    SDL_DestroyTexture(enemy2T);
    SDL_DestroyTexture(enemy3T);
    SDL_DestroyTexture(enemy4T);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
}

Player* SDLFactory::getPlayer()
{
    playerR = {400,600,playerR.w,playerR.h};
    return new SDLPlayer(sdlRender,playerT,&playerR);

}

Rocket* SDLFactory::getRocket(int x, int y, int type)
{
    if(type == 1)
    {
        rocket1R = {x,y,rocket1R.w,rocket1R.h};
        return new SDLRocket(sdlRender,rocket1T,&rocket1R,type);
    }
    else if(type == 2)
    {
        rocket2R = {x,y,rocket2R.w,rocket2R.h};
        return new SDLRocket(sdlRender,rocket2T,&rocket2R,type);
    }
    else
        return 0;
}

Enemy* SDLFactory::getEnemy(int x, int y, int type)
{
    switch(type)
    {
        case 1:
            enemy1R = {x,y,enemy1R.w,enemy1R.h};
            return new SDLEnemy(sdlRender,enemy1T,&enemy1R,type);
        case 2:
            enemy2R = {x,y,enemy2R.w,enemy2R.h};
            return new SDLEnemy(sdlRender,enemy2T,&enemy2R,type);
        case 3:
            enemy3R = {x,y,enemy3R.w,enemy3R.h};
            return new SDLEnemy(sdlRender,enemy3T,&enemy3R,type);
        case 4:
            enemy4R = {x,y,enemy4R.w,enemy4R.h};
            return new SDLEnemy(sdlRender,enemy4T,&enemy4R,type);
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
        Mix_PlayChannel(-1,rocket1M,0);
    else
        Mix_PlayChannel(-1,rocket2M,0);
}
