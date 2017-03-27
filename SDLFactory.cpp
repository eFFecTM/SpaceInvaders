#include <algorithm>
#include "SDLFactory.h"
#include "SDLPlayer.h"
#include "SDLRocket.h"
#include "SDLEnemy.h"

namespace NSSDL
{
    SDLFactory::SDLFactory()
    {
        SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1"); // Fixes debugging
        SDL_Init(SDL_INIT_EVERYTHING);
        TTF_Init();
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
        SDL_StopTextInput();

        window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600,
                                  SDL_WINDOW_RESIZABLE);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        menuT = createTextureFromImage("resources/Menu.bmpx", &menuR);
        backgroundT = createTextureFromImage("resources/Background.bmpx", &backgroundR);
        pausedT = createTextureFromImage("resources/Paused.bmpx", &backgroundR); // Same size as background rect, so reusing it
        gameOverT = createTextureFromImage("resources/GameOver.bmpx", &backgroundR);
        controlsT = createTextureFromImage("resources/Controls.bmpx",&backgroundR);

        fontSmall = TTF_OpenFont("resources/Impact.ttf", 32);
        fontLarge = TTF_OpenFont("resources/Impact.ttf", 96);
        fontMonospace = TTF_OpenFont("resources/Joystix_Monospace.ttf", 24);

        std::string text[4] = {"PLAY GAME","HIGHSCORES","CONTROLS","EXIT GAME"};
        for(int i=0; i<4; i++)
        {
            menuOptionTextureList[i] = createTextureFromText(fontSmall, text[i], {255, 255, 255}, &menuOptionRectList[i]);
            menuSelectedOptionTextureList[i] = createTextureFromText(fontSmall, text[i], {0, 255, 0}, &menuOptionRectList[i]);
        }

        playerT = createTextureFromImage("resources/SpaceShip.bmpx", &playerR);
        rocket1T = createTextureFromImage("resources/Rocket1.bmpx", &rocket1R);
        rocket2T = createTextureFromImage("resources/Rocket2.bmpx", &rocket2R);
        enemy1T = createTextureFromImage("resources/Enemy1.bmpx", &enemy1R);
        enemy2T = createTextureFromImage("resources/Enemy2.bmpx", &enemy2R);
        enemy3T = createTextureFromImage("resources/Enemy3.bmpx", &enemy3R);
        enemy4T = createTextureFromImage("resources/Enemy4.bmpx", &enemy4R);

//    music = Mix_LoadMUS("resources/Mass_Effect_Uncharted_Worlds.mp3");
        music = Mix_LoadMUS("resources/Icarus_8bit.mp3");
        Mix_VolumeMusic(MIX_MAX_VOLUME / 8);
        Mix_FadeInMusic(music, -1, 5000);

        rocket1M = Mix_LoadWAV("resources/rocket1.wav");
        Mix_VolumeChunk(rocket1M, MIX_MAX_VOLUME / 4);

        rocket2M = Mix_LoadWAV("resources/rocket2.wav");
        Mix_VolumeChunk(rocket2M, MIX_MAX_VOLUME / 4);

        highscoreLogoT = createTextureFromText(fontLarge, "HIGHSCORES", {255, 140, 0}, &highscoreLogoR);
        std::stringstream ss;
        ss << "PLACE     NAME          SCORE";
        scoreXT = createTextureFromText(fontMonospace, ss.str().c_str(), {255, 255, 255}, &scoreXR);
        ss.str("");
        ss.clear();
        ss << ".         ...           ...";
        scoreEmptyT = createTextureFromText(fontMonospace, ss.str().c_str(), {255, 255, 255}, &scoreEmptyR);

        newHighscoreLogoT = createTextureFromText(fontLarge, "NEW HIGHSCORE!", {255, 140, 0}, &newHighscoreLogoR);
        newHighscoreInstrT = createTextureFromText(fontSmall, "Type your name here, then press enter:", {255, 255, 255}, &newHighscoreInstrR);

        sdlRender = new SDLRender(renderer);
    }

    Event SDLFactory::getEvent()
    {
        SDL_Event event;
        Event e = Default;

        while (SDL_PollEvent(&event) != 0) // handle all events in queue first!
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    e = Close;
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                    {
                        sdlRender->updateWindowSize(event.window.data1, event.window.data2);
                    }
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                        case SDL_SCANCODE_P:
                            if (!event.key.repeat)
                                e = Pause;
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
                        case SDL_SCANCODE_BACKSPACE:
                            if (inputText.length() > 0)
                            {
                                inputText.pop_back();
                                renderNewInputText = true;
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_TEXTINPUT:
                    if(inputText.length() < 10)
                    {
                        inputText += event.text.text;
                        std::cout << "Text:" << inputText << std::endl;
                        renderNewInputText = true;
                    }
                    break;
                default:
                    break;
            }
        }

        const Uint8 *currentKeystates = SDL_GetKeyboardState(NULL);
        if (currentKeystates[SDL_SCANCODE_LEFT])
        {
            if (currentKeystates[SDL_SCANCODE_SPACE])
                e = LeftShoot;
            else if (!currentKeystates[SDL_SCANCODE_RIGHT])
                e = Left;
        } else if (currentKeystates[SDL_SCANCODE_RIGHT])
        {
            if (currentKeystates[SDL_SCANCODE_SPACE])
                e = RightShoot;
            else
                e = Right;
        } else if (currentKeystates[SDL_SCANCODE_SPACE])
            e = Shoot;

        return e;
    }

    SDL_Texture *SDLFactory::createTextureFromImage(std::string path, SDL_Rect *rect)
    {
        SDL_Surface *surface = SDL_LoadBMP(path.c_str());
        SDL_GetClipRect(surface, rect);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        return texture;
    }

    SDL_Texture *SDLFactory::createTextureFromText(TTF_Font *font, std::string text, SDL_Color color, SDL_Rect *rect)
    {
        SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), color);
        SDL_GetClipRect(surface, rect);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        return texture;
    }

    void SDLFactory::renderBackground()
    {
        SDL_RenderClear(renderer);
        sdlRender->render(backgroundT, backgroundR);
    }

    void SDLFactory::renderMenu(int selectedOption)
    {
        SDL_Rect rect = {100, 0, menuR.w, menuR.h};
        sdlRender->render(menuT, rect);

        for(int i=0; i<4; i++)
        {
            if(selectedOption == i)
                sdlRender->render(menuSelectedOptionTextureList[i], {400 - menuOptionRectList[i].w / 2, 300+i*(25+menuOptionRectList[0].h), menuOptionRectList[i].w,menuOptionRectList[i].h});
            else
                sdlRender->render(menuOptionTextureList[i], {400 - menuOptionRectList[i].w / 2, 300+i*(25+menuOptionRectList[0].h), menuOptionRectList[i].w, menuOptionRectList[i].h});
        }
    }

    void SDLFactory::renderPaused()
    {
        sdlRender->render(pausedT, backgroundR);
    }

    void SDLFactory::renderScore(int score)
    {
        SDL_DestroyTexture(scoreT);
        std::stringstream ss;
        ss << "Score: " << score;
        scoreT = createTextureFromText(fontSmall, ss.str().c_str(), {255, 255, 255}, &scoreR);
        sdlRender->render(scoreT, scoreR);
    }

    void SDLFactory::renderLives(int lives)
    {
        SDL_DestroyTexture(livesT);
        std::stringstream ss;
        ss << "Lives left: " << lives;
        livesT = createTextureFromText(fontSmall, ss.str().c_str(), {255, 0, 0}, &livesR);
        sdlRender->render(livesT, {800 - livesR.w, 0, livesR.w, livesR.h});
    }

    void SDLFactory::renderCurrentHighscore(int score)
    {
        SDL_DestroyTexture(currentHighscoreT);
        std::stringstream ss;
        ss << "Highscore: " << score;
        currentHighscoreT = createTextureFromText(fontSmall, ss.str().c_str(), {255, 140, 0}, &currentHighscoreR);
        sdlRender->render(currentHighscoreT, {400 - currentHighscoreR.w/2, 0, currentHighscoreR.w, currentHighscoreR.h});
    }

    void SDLFactory::renderPresent()
    {
        SDL_RenderPresent(renderer);
    }

    SDLFactory::~SDLFactory()
    {
        SDL_DestroyTexture(scoreXT);
        Mix_FreeChunk(rocket1M);
        Mix_FreeChunk(rocket2M);
        Mix_FreeMusic(music);
        SDL_DestroyTexture(livesT);
        SDL_DestroyTexture(scoreT);
        SDL_DestroyTexture(backgroundT);
        SDL_DestroyTexture(menuT);
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

    NSGame::Player *SDLFactory::getPlayer()
    {
        playerR = {400, 600, playerR.w, playerR.h};
        return new SDLPlayer(sdlRender, playerT, &playerR);

    }

    NSGame::Rocket *SDLFactory::getRocket(int x, int y, int type)
    {
        if (type == 1)
        {
            rocket1R = {x, y, rocket1R.w, rocket1R.h};
            return new SDLRocket(sdlRender, rocket1T, &rocket1R, type);
        } else if (type == 2)
        {
            rocket2R = {x, y, rocket2R.w, rocket2R.h};
            return new SDLRocket(sdlRender, rocket2T, &rocket2R, type);
        } else
            return 0;
    }

    NSGame::Enemy *SDLFactory::getEnemy(int x, int y, int type)
    {
        switch (type)
        {
            case 1:
                enemy1R = {x, y, enemy1R.w, enemy1R.h};
                return new SDLEnemy(sdlRender, enemy1T, &enemy1R, type);
            case 2:
                enemy2R = {x, y, enemy2R.w, enemy2R.h};
                return new SDLEnemy(sdlRender, enemy2T, &enemy2R, type);
            case 3:
                enemy3R = {x, y, enemy3R.w, enemy3R.h};
                return new SDLEnemy(sdlRender, enemy3T, &enemy3R, type);
            case 4:
                enemy4R = {x, y, enemy4R.w, enemy4R.h};
                return new SDLEnemy(sdlRender, enemy4T, &enemy4R, type);
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
        if (type == 1)
            Mix_PlayChannel(-1, rocket1M, 0);
        else
            Mix_PlayChannel(-1, rocket2M, 0);
    }

    void SDLFactory::makeHighscore(std::vector<Score> *highscore)
    {
        std::stringstream ss;
        std::string s;
        for (unsigned int i = 0; i < highscore->size(); i++)
        {
            SDL_DestroyTexture(scoreTextureList[i]);
            Score score = highscore->at(i);
            ss.str("");
            ss.clear();
            s.clear();
            s.append(14 - score.name.length(), ' ');
            ss << i + 1 << "         " << score.name << s << score.score;
            scoreTextureList[i] = createTextureFromText(fontMonospace, ss.str().c_str(), {255, 255, 255},
                                                        &scoreRectList[i]);
        }
    }

    void SDLFactory::renderHighscore(int size)
    {
        sdlRender->render(highscoreLogoT, {400 - highscoreLogoR.w / 2, 50, highscoreLogoR.w, highscoreLogoR.h});
        sdlRender->render(scoreXT, {400 - scoreXR.w / 2, 200, scoreXR.w, scoreXR.h});
        for (int i = 0; i < 5; i++)
            if (i < size)
                sdlRender->render(scoreTextureList[i],
                                  {400 - scoreXR.w / 2, 200 + scoreXR.h * (i + 1), scoreRectList[i].w,
                                   scoreRectList[i].h});
            else
                sdlRender->render(scoreEmptyT,
                                  {400 - scoreXR.w / 2, 200 + scoreXR.h * (i + 1), scoreEmptyR.w, scoreEmptyR.h});

    }

    void SDLFactory::renderGameOver()
    {
        sdlRender->render(gameOverT, backgroundR);
    }

    std::string SDLFactory::getInputText()
    {
        SDL_StopTextInput();
        inputText.erase(std::remove_if(inputText.begin(), inputText.end(), ::isspace), inputText.end());
        std::transform(inputText.begin(), inputText.end(), inputText.begin(), ::toupper);
        std::cout << inputText << std::endl;
        return inputText;
    }

    void SDLFactory::enableTextInput()
    {
        inputText = "";
        SDL_StartTextInput();
    }

    void SDLFactory::renderNewHighscore()
    {
        sdlRender->render(newHighscoreLogoT,
                          {400 - newHighscoreLogoR.w / 2, 50, newHighscoreLogoR.w, newHighscoreLogoR.h});
        sdlRender->render(newHighscoreInstrT,
                          {400 - newHighscoreInstrR.w / 2, 200, newHighscoreInstrR.w, newHighscoreInstrR.h});

        if (renderNewInputText)
        {
            SDL_DestroyTexture(newInputTextT);
            newInputTextT = createTextureFromText(fontMonospace, inputText, {255, 0, 0}, &newInputTextR);
        }

        sdlRender->render(newInputTextT, {400 - newHighscoreInstrR.w / 2, 200 + newHighscoreInstrR.h, newInputTextR.w,
                                          newInputTextR.h});

    }

    void SDLFactory::renderControls()
    {
        sdlRender->render(controlsT,backgroundR);
    }
}
