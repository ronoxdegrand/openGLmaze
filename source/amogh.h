#include "main.h"

#ifndef AMOGH_H
#define AMOGH_H

class Amogh
{
public:
    Amogh() {}
    Amogh(float x, float y);
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
