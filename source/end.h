#include "main.h"

#ifndef END_H
#define END_H

class End
{
public:
    End() {}
    End(bool eh);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
    double speed;

private:
    VAO *object;
};

#endif
