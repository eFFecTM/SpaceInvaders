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
    Event getEvent();
    void renderBackground();
    void renderMenu();
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
    SDL_Surface* backgroundS=NULL,*menuS=NULL,*scoreS=NULL,*livesS=NULL,*rocket1S=NULL,*rocket2S=NULL,*playerS=NULL,*enemy1S=NULL,*enemy2S=NULL,*enemy3S=NULL,*enemy4S=NULL;
    SDL_Rect backgroundRect,menuRect,scoreRect,livesRect;
    SDL_Texture* backGroundTexture = NULL,*menuTexture = NULL;
    int windowWidth = 800, windowHeight = 600;
    TTF_Font* font = NULL;
    SDL_Texture* scoreTexture = NULL,*livesTexture = NULL;
    Mix_Music* music = NULL;
    Mix_Chunk *rocket1 = NULL, *rocket2 = NULL;
    int startTicks = 0;
};

#endif //SPACEINVADERS_SDLFACTORY_H
