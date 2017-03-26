#ifndef SPACEINVADERS_SDLFACTORY_H
#define SPACEINVADERS_SDLFACTORY_H

#include "AbstractFactory.h"
#include "SDLRender.h"
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
    SDL_Texture* createTextureFromImage(std::string,SDL_Rect*);
    SDL_Texture* createTextureFromText(TTF_Font*,std::string,SDL_Color,SDL_Rect*);
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
    void makeHighscore(std::vector<Score>*);
    void renderHighscore(int);
    void renderGameOver();
    std::string getInputText();
    void enableTextInput();
    void renderNewHighscore();
private:
    SDL_Window* window = NULL; // Good practice
    SDL_Renderer* renderer = NULL;
    SDL_Rect menuR,backgroundR,scoreR,livesR,playerR,rocket1R,rocket2R,enemy1R,enemy2R,enemy3R,enemy4R,menuOption1R,menuOption2R,menuOption3R;
    SDL_Rect scoreXR, scoreEmptyR, highscoreLogoR, newHighscoreLogoR, newHighscoreInstrR, newInputTextR;
    SDL_Texture *menuT=NULL,*backgroundT=NULL,*scoreT=NULL,*livesT=NULL,*pausedT=NULL,*playerT=NULL,*rocket1T=NULL,*rocket2T=NULL,*enemy1T=NULL,*enemy2T=NULL,*enemy3T=NULL,*enemy4T=NULL;
    SDL_Texture *menuOption1T=NULL,*menuSelectedOption1T=NULL,* menuOption2T=NULL,*menuSelectedOption2T=NULL,*menuOption3T=NULL,*menuSelectedOption3T=NULL;
    SDL_Texture *scoreXT=NULL,*scoreEmptyT=NULL,*highscoreLogoT=NULL,*gameOverT=NULL,*newHighscoreLogoT=NULL,*newInputTextT=NULL,*newHighscoreInstrT=NULL;
    TTF_Font* fontSmall = NULL,*fontLarge = NULL,*fontMonospace = NULL;
    Mix_Music* music = NULL;
    Mix_Chunk *rocket1M = NULL, *rocket2M = NULL;
    int startTicks = 0;
    SDLRender* sdlRender = NULL;
    SDL_Texture* scoreTextureList[5] = {NULL};
    SDL_Rect scoreRectList[5];
    std::string inputText = "";
    bool renderNewInputText = false;
};

#endif //SPACEINVADERS_SDLFACTORY_H
