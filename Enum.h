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