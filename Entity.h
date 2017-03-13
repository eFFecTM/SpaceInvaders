#ifndef SPACEINVADERS_ENTITY_H
#define SPACEINVADERS_ENTITY_H

class Entity
{
public:
    Entity(int,int,int,int);
    int* getX();
    int* getY();
    int* getWidth();
    int* getHeight();
    void setX(int);
    void setY(int);
    void setWidth(int);
    void setHeight(int);
    virtual void render() = 0;
protected:
    int x, y, width, height;
};

#endif //SPACEINVADERS_ENTITY_H
