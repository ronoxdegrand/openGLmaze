#include "main.h"

#ifndef MAZE_H
#define MAZE_H

class Maze
{
public:
    Maze() {}
    Maze(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bool renderx[6][6];
    bool rendery[6][6];

private:
    VAO *object;
};

#endif
