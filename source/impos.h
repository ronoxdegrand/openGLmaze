#include "main.h"

#ifndef IMPOS_H
#define IMPOS_H

class Impos
{
public:
    Impos() {}
    Impos(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;

private:
    VAO *object;
};

#endif
