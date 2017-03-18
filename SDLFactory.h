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
    void renderScore(int);
    void renderPresent();
    void startTimer();
    int getTickDifference();
    void addDelay(int);
    void playSoundEffect(int);
private:
    SDL_Window* window = NULL; // Good practice
    SDL_Renderer* renderer = NULL;
    SDL_Surface* surface = NULL;
    SDL_Rect backgroundRect, textRect;
    SDL_Texture* backGroundTexture = NULL;
    int windowWidth = 800, windowHeight = 600;
    TTF_Font* font = NULL;
    SDL_Texture* textTexture = NULL;
    Mix_Music* music = NULL;
    Mix_Chunk *rocket1 = NULL, *rocket2 = NULL;
    int startTicks = 0;
};

#endif //SPACEINVADERS_SDLFACTORY_H
