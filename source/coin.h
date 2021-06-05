#include "main.h"

#ifndef COIN_H
#define COIN_H

class Coin
{
public:
    Coin() {}
    Coin(float x, float y, bool upordown);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    //void set_position(float x, float y);
    void tick();
    double speed;

private:
    VAO *object;
};

#endif
