#include "Entity.h"

Entity::Entity(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

int* Entity::getX()
{
    return &x;
}

int* Entity::getY()
{
    return &y;
}

int* Entity::getWidth()
{
    return &width;
}

int* Entity::getHeight()
{
    return &height;
}

void Entity::setX(int x)
{
    this -> x = x;

}

void Entity::setY(int y)
{
    this -> y = y;
}

void Entity::setWidth(int w)
{
    width = w;

}

void Entity::setHeight(int h)
{
    height = h;
}