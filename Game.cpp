#include "Game.h"

Game::Game(AbstractFactory* af)
{
    this->af = af;
}

void Game::start()
{
    readHighscores();

    while(running)
    {
        af->startTimer();
        Event e;
        e = af->getEvent();
        running = handleEvent(e);
        af->renderBackground();
        switch(mode)
        {
            case Menu:
                menu();
                break;
            case Playing:
                playing();
                checkDead();
                break;
            case Paused:
                paused();
                break;
            case Highscores:
                af->renderHighscore(highscore.size());
                break;
            case GameOver:
                af->renderGameOver();
                break;
            case NewHighscore:
                if(!inputText.empty())
                    addNewHighscore();
                af->renderNewHighscore();
                break;
            default:
                break;
        }
        af->renderPresent();
        int frameTicks = af->getTickDifference();
        if (frameTicks < 1000 / 50) // Limiting framerate to 50 fps (60 has no round number)
            af->addDelay(1000 / 50 - frameTicks);
    }

    writeHighscores();
}

void Game::checkDead()
{
    if(*player->getLives() == 0)
    {
        for (Rocket* r : playerRockets)
        {
            delete r;
        }
        playerRockets.clear();

        for (Rocket* r : enemyRockets)
        {
            delete r;
        }
        enemyRockets.clear();

        for (Enemy* enemy : enemies)
        {
            delete enemy;
        }
        enemies.clear();

        if(*player->getScore() > highscore.back().score || highscore.size() != 5)
        {
            mode = NewHighscore;
            af->enableTextInput();
        }
        else
        {
            mode = GameOver;
        }
        delete player;
        isFirstPlaying = true;
    }
}

void Game::menu()
{
    af->renderMenu(selectedOption);
}

void Game::playing()
{
    if(isFirstPlaying)
    {
        if(continuePlaying)
            continuePlaying = false;
        else
            player = af->getPlayer();
        ls = 25; // left side border
        rs = 750; // right side border
        us = 50; // up side border
        bs = 600-*player->getHeight(); // bottom side border
        for(unsigned int i=0; i<10; i++)
        {
            enemies.push_back(af->getEnemy(ls+60*i,us,1));
            enemies.push_back(af->getEnemy(ls+60*i,us+50,2));
            enemies.push_back(af->getEnemy(ls+60*i,us+2*50,3));
            enemies.push_back(af->getEnemy(ls+60*i,us+3*50,4));
        }
        isFirstPlaying = false;
    }

    if (i == 25)
    {
        moveEnemies();
        shootEnemies();
        i = 0;
    }
    i++;

    moveRockets();
    collisionDetection();
    af->renderScore(*player->getScore());
    af->renderLives(*player->getLives());
    player->render();

    for (Enemy* enemy : enemies)
        enemy->render();
    for (Rocket* rocket : playerRockets)
        rocket->render();
    for (Rocket* rocket : enemyRockets)
        rocket->render();
    if(enemies.empty())
    {
        isFirstPlaying = true;
        continuePlaying = true;
    }
}

void Game::paused()
{
    af->renderScore(*player->getScore());
    af->renderLives(*player->getLives());
    player->render();

    for (Enemy* enemy : enemies)
        enemy->render();
    for (Rocket* rocket : playerRockets)
        rocket->render();
    for (Rocket* rocket : enemyRockets)
        rocket->render();

    af->renderPaused();
}

void Game::addNewHighscore()
{
    bool hasInserted = false;
    Score score = {inputText,*player->getScore()};
    unsigned int size = highscore.size();
    for(unsigned int i=0; i<size; i++)
    {
        if(*player->getScore() > highscore.at(i).score)
        {
            highscore.insert(highscore.begin()+i,score);
            hasInserted = true;
        }
    }

    if(!hasInserted)
        highscore.at(size) = score;

    if(size > 5)
        highscore.pop_back();

    inputText = "";
    af->makeHighscore(&highscore);
}

bool Game::handleEvent(Event e)
{
    bool running = true;

    switch(e)
    {
        case Close:
            running = false;
            break;
        case Left:
            if(mode == Playing)
                movePlayer(Left);
            break;
        case Right:
            if(mode == Playing)
                movePlayer(Right);
            break;
        case Shoot:
            if(mode == Playing)
                shootPlayer();
            break;
        case LeftShoot:
            if(mode == Playing)
            {
                movePlayer(Left);
                shootPlayer();
            }
            break;
        case RightShoot:
            if(mode == Playing)
            {
                movePlayer(Right);
                shootPlayer();
            }
            break;
        case Pause:
        {
            if(mode == Playing)
                mode = Paused;
            else if(mode == Paused)
                mode = Playing;
            break;
        }
        case MenuEnter:
        {
            if(mode == Menu)
            {
                switch(selectedOption)
                {
                    case 1:
                        mode = Playing;
                        break;
                    case 2:
                        mode = Highscores;
                        break;
                    case 3:
                        running = false;
                        break;
                    default:
                        break;
                }
            }
            else if(mode == Highscores || mode == GameOver)
                mode = Menu;
            else if(mode == NewHighscore)
            {
                inputText = af->getInputText();
                mode = Highscores;
            }
            break;
        }
        case MenuUp:
            if(mode == Menu && selectedOption > 1)
                selectedOption--;
            break;
        case MenuDown:
            if(mode == Menu && selectedOption < 3)
                selectedOption++;
            break;
        default:
            break;
    }
    return running;
}

void Game::shootPlayer() // Player shoots
{
    int x,y;
    if(playerRockets.size() < 1) // Max 1 playerRockets in existence
    {
        x = *player->getX()+ *player->getWidth()/2;
        y = *player->getY();
        playerRockets.push_back(af->getRocket(x,y,1));
        af->playSoundEffect(1);
    }
}

void Game::shootEnemies() // Enemies shoots (random)
{

    if(enemyRockets.size() < 1) // Max 1 enemyRockets in existence
    {
        int size = enemies.size();
        srand((unsigned int) time(0));
        int r = rand() % size; // 0 tot en met 31
        Enemy* enemy = enemies.at((unsigned int) r);
        int x = *enemy->getX() + *enemy->getWidth()/2;;
        int y = *enemy->getY() + *enemy->getHeight()/2;
        enemyRockets.push_back(af->getRocket(x,y,2));
        af->playSoundEffect(2);
    }
}

void Game::movePlayer(Event e)
{
    if(e == Left && *player->getX() > 0)
        player->setX(*player->getX() - 5);
    else if(*player->getX() < 800-*player->getWidth())
        player->setX(*player->getX() + 5);
}

void Game::moveRockets()
{
    Rocket* rocket;
    for(unsigned int i=0; i<playerRockets.size(); i++)
    {
        rocket = playerRockets.at(i);
        if (*rocket->getY() > -*rocket->getHeight())
            rocket->setY(*rocket->getY() - 10);
        else
        {
            delete rocket;
            playerRockets.erase(playerRockets.begin() + i);
        }
    }

    for(unsigned int i=0; i<enemyRockets.size(); i++)
    {
        rocket = enemyRockets.at(i);
        if(*rocket->getY() < 600)
            rocket->setY(*rocket->getY() + 10);
        else
        {
            delete rocket;
            enemyRockets.erase(enemyRockets.begin() + i);
        }
    }
}

void Game::moveEnemies()
{
    bool isMovingDown = false;

    for(Enemy* enemy : enemies)
    {
        if(right && *enemy->getX() > rs)
        {
            isMovingDown = true;
            right = false;
            break;
        }
        else if(!right && *enemy->getX() < ls)
        {
            isMovingDown = true;
            right = true;
            break;
        }
    }

    if(isMovingDown)
    {
        for(Enemy* enemy : enemies)
        {
            enemy->setY(*enemy->getY()+50);
        }
    }
    else
    {
        for(Enemy* enemy : enemies)
        {
            if (right)
            {
                enemy->setX(*enemy->getX() + 5);
            }
            else // going left
            {
                enemy->setX(*enemy->getX() - 5);
            }
        }
    }
}

void Game::collisionDetection()
{
    Enemy* enemy;
    Rocket* rocket;
    for(unsigned int i=0;i<enemies.size();i++)
    {
        for(unsigned int j=0;j<playerRockets.size();j++)
        {
            enemy = enemies.at(i);
            rocket = playerRockets.at(j);

            if(hasIntersection(enemy,rocket))
            {
                switch(*enemy->getType())
                {
                    case 1:
                        player->setScore(*player->getScore() += 10);
                        break;
                    case 2:
                        player->setScore(*player->getScore() += 20);
                        break;
                    case 3:
                        player->setScore(*player->getScore() += 30);
                        break;
                    case 4:
                        player->setScore(*player->getScore() += 50);
                        break;
                    default:
                        break;
                }

                delete enemy;
                enemies.erase(enemies.begin() + i);
                delete rocket;
                playerRockets.erase(playerRockets.begin() + j);
                break;
            }
        }
    }

    for(unsigned int i=0;i<enemyRockets.size();i++)
    {
        rocket = enemyRockets.at(i);

        if(hasIntersection(player,rocket))
        {
            delete rocket;
            player->setLives(*player->getLives()-= 1);
            player->setX(400-*player->getWidth()/2);
            player->setY(600-*player->getHeight());
            enemyRockets.erase(enemyRockets.begin() + i);
            break;
        }
    }
}

// Algorithm from SDL library: SDL_rect.c (om gamecode in game te houden)
// Source code available on https://www.libsdl.org/
// A is enemy, B is rocket
bool Game::hasIntersection(Entity* A, Entity* B)
{
    int Amin, Amax, Bmin, Bmax;

    /* Horizontal intersection */
    Amin = *A->getX();
    Amax = Amin + *A->getWidth();
    Bmin = *B->getX();
    Bmax = Bmin + *B->getWidth();
    if (Bmin > Amin)
        Amin = Bmin;
    if (Bmax < Amax)
        Amax = Bmax;
    if (Amax <= Amin)
        return false;

    /* Vertical intersection */
    Amin = *A->getY();
    Amax = Amin + *A->getHeight();
    Bmin = *B->getY();
    Bmax = Bmin + *B->getHeight();
    if (Bmin > Amin)
        Amin = Bmin;
    if (Bmax < Amax)
        Amax = Bmax;
    if (Amax <= Amin)
        return false;

    return true;
}

void Game::readHighscores()
{
    stringstream ss;
    string s,part;
    ifstream file("resources/Highscores.txt");
    while(getline(file,s))
    {
        ss.clear();
        ss.str(s);
        Score score = Score();
        int i=0;
        while(getline(ss,part,';'))
        {
            if(i == 0)
                score.name = part;
            else
                score.score = strtol(part.c_str(),nullptr,0);
            i++;
        }
        highscore.push_back(score);
    }

    for(Score score : highscore)
        cout << "Name: " << score.name << "  ; Score: " << score.score << endl;

    file.close();

    af->makeHighscore(&highscore);
}

void Game::writeHighscores()
{
    ofstream file("resources/Highscores.txt");
    for(Score score : highscore)
        file << score.name << ";" << score.score << endl;
    file.close();
}
