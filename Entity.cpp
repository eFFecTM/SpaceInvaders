/**
 * Entity class: More info at the header class
 */

#include "Entity.h"

namespace NSGame
{
    Entity::Entity() {}

    int *Entity::getX()
    {
        return &x;
    }

    int *Entity::getY()
    {
        return &y;
    }

    int *Entity::getWidth()
    {
        return &width;
    }

    int *Entity::getHeight()
    {
        return &height;
    }

    void Entity::setX(int x)
    {
        this->x = x;

    }

    void Entity::setY(int y)
    {
        this->y = y;
    }

    void Entity::setWidth(int w)
    {
        width = w;

    }

    void Entity::setHeight(int h)
    {
        height = h;
    }
}