/**
 * Header for Enemy class
 * Contains type of enemy, fields can be get
 */

#ifndef SPACEINVADERS_ENEMY_H
#define SPACEINVADERS_ENEMY_H

#include "Entity.h"

namespace NSGame
{
    class Enemy : public Entity
    {
    public:
        Enemy(){}
        virtual ~Enemy(){}
        virtual int *getType() = 0;
    protected:
        int type;
    };
}

#endif //SPACEINVADERS_ENEMY_H
