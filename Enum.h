/**
 * Contains a (game)Event and (game)Mode enumerator
 * Also contains a struct Score for the scoreboard of the game
 */

#ifndef SPACEINVADERS_ENUM_H
#define SPACEINVADERS_ENUM_H

#endif //SPACEINVADERS_ENUM_H

enum Event
{
    Default,
    Close,
    Left,
    Right,
    LeftShoot,
    RightShoot,
    Shoot,
    MenuEnter,
    MenuUp,
    MenuDown,
    Pause
};

enum Mode
{
    Menu,
    Playing,
    Paused,
    Highscores,
    GameOver,
    NewHighscore,
    Controls
};

struct Score
{
    std::string name;
    int score;
};