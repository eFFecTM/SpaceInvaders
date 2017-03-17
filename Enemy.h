#ifndef SPACEINVADERS_ENEMY_H
#define SPACEINVADERS_ENEMY_H

#include "Entity.h"

class Enemy : public Entity
{
public:
    Enemy(){}
    virtual ~Enemy(){}
    virtual int* getType() = 0;
protected:
    int type;
};

#endif //SPACEINVADERS_ENEMY_H