#ifndef SPACEINVADERS_ROCKET_H
#define SPACEINVADERS_ROCKET_H

#include "Player.h"

namespace NSGame
{
    class Rocket : public Player
    {
    public:
        Rocket()
        {}

        virtual ~Rocket()
        {}

        virtual int *getType() = 0;

    protected:
        int type;
    };
}

#endif //SPACEINVADERS_ROCKET_H
