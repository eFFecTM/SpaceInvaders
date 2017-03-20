#ifndef SPACEINVADERS_SDLFACTORY_H
#define SPACEINVADERS_SDLFACTORY_H

#include "AbstractFactory.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_Mixer.h>

class SDLFactory : public AbstractFactory
{
public:
    SDLFactory();
    virtual ~SDLFactory();
    Player* getPlayer();
    Rocket* getRocket(int,int,int);
    Enemy* getEnemy(int,int,int);
    Enum getEvent();
    void renderBackground();
    void renderMenu(int);
    void renderPaused();
    void renderScore(int);
    void renderLives(int);
    void renderPresent();
    void startTimer();
    int getTickDifference();
    void addDelay(int);
    void playSoundEffect(int);
private:
    SDL_Window* window = NULL; // Good practice
    SDL_Renderer* renderer = NULL;
    SDL_Surface* surface=NULL,*backgroundS=NULL,*menuS=NULL,*scoreS=NULL,*livesS=NULL,*rocket1S=NULL,*rocket2S=NULL,*playerS=NULL,*enemy1S=NULL,*enemy2S=NULL,*enemy3S=NULL,*enemy4S=NULL;
    SDL_Rect backgroundRect,menuRect,scoreRect,livesRect,menuOption1Rect,menuOption2Rect,menuOption3Rect;
    SDL_Texture* backGroundTexture = NULL,*menuTexture = NULL,*scoreTexture = NULL,*livesTexture = NULL,*pausedTexture=NULL;
    SDL_Texture* menuOption1T=NULL,*menuSelectedOption1T=NULL;
    SDL_Texture* menuOption2T=NULL,*menuSelectedOption2T=NULL;
    SDL_Texture* menuOption3T=NULL,*menuSelectedOption3T=NULL;
    int windowWidth = 800, windowHeight = 600;
    TTF_Font* font = NULL;
    Mix_Music* music = NULL;
    Mix_Chunk *rocket1 = NULL, *rocket2 = NULL;
    int startTicks = 0;
};

#endif //SPACEINVADERS_SDLFACTORY_H
