/**
 * Header for Entity class
 * Contains x/y coordinates, width and height, fields can be set and get
 */

#ifndef SPACEINVADERS_ENTITY_H
#define SPACEINVADERS_ENTITY_H

#include <iostream>

namespace NSGame
{
    class Entity
    {
    public:
        Entity();
        int *getX();
        int *getY();
        int *getWidth();
        int *getHeight();
        void setX(int);
        void setY(int);
        void setWidth(int);
        void setHeight(int);
        virtual void render() = 0;
        virtual ~Entity(){}
    protected:
        int x, y, width, height;
    };
}

#endif //SPACEINVADERS_ENTITY_H
