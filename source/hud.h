#include "main.h"

#ifndef HUD_H
#define HUD_H

class Hud
{
public:
    Hud() {}
    Hud(int eh);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    //void set_lives(float x);
    void tick();
    double speed;
    //int lives;

private:
    VAO *object;
};

#endif
