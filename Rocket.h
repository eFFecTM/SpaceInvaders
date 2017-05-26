/**
 * Header for Rocket class
 * Contains type of rocket
 */

#ifndef SPACEINVADERS_ROCKET_H
#define SPACEINVADERS_ROCKET_H

#include "Player.h"

namespace NSGame
{
    class Rocket : public Entity
    {
    public:
        Rocket(){}
        virtual ~Rocket(){}
    protected:
        int type;
    };
}

#endif //SPACEINVADERS_ROCKET_H
