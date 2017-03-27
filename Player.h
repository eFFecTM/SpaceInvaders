#ifndef SPACEINVADERS_PLAYER_H
#define SPACEINVADERS_PLAYER_H

#include "Entity.h"

namespace NSGame
{
    class Player : public Entity
    {
    public:
        Player()
        {};

        virtual ~Player()
        {}

        int *getScore();

        void setScore(int);

        int *getLives();

        void setLives(int);

    private:
        int lives = 3;
        int score = 0;
    };
}

#endif //SPACEINVADERS_PLAYER_H
