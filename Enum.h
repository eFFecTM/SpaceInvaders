#ifndef SPACEINVADERS_ENUM_H
#define SPACEINVADERS_ENUM_H

#endif //SPACEINVADERS_ENUM_H

enum Enum
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
    NewHighscore
};

struct Userscore
{
    int score;
    int name;
};