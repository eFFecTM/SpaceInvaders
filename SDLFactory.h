#ifndef SPACEINVADERS_SDLFACTORY_H
#define SPACEINVADERS_SDLFACTORY_H

#include "AbstractFactory.h"
#include <SDL.h>
#include <SDL_ttf.h>

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
    void renderPresent();
private:
    SDL_Window* window = NULL; // Good practice
    SDL_Renderer* renderer = NULL;
    SDL_Surface* surface = NULL;
    SDL_Rect backgroundRect, textRect;
    SDL_Texture* backGroundTexture = NULL;
    int windowWidth = 800, windowHeight = 600;
    TTF_Font* font = NULL;
    SDL_Texture* textTexture = NULL;
};

#endif //SPACEINVADERS_SDLFACTORY_H
