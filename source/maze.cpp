#include "maze.h"
#include "main.h"
#include <stack>
#include <utility>
#include <stdlib.h>
#include <time.h>

Maze::Maze(float x, float y, color_t color)
{
    srand(time(0));

    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;

    int sizex2 = 72;

    /* MAZE GENERATION ALGORITHM BEGINS */
    //0,0 is bottom left; 5,5 is top right
    std::stack<std::pair<int, int>> whereareyounow;
    std::stack<std::pair<int, int>> neighbours;
    bool visited[6][6] = {};

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
        {
            this->renderx[i][j] = false;
            this->rendery[i][j] = false;
        }

    int exit = 1;
    whereareyounow.push(std::make_pair(0, 0));
    int currx = 0, curry = 0;
    visited[0][0] = true;
    while (exit < 36)
    {
        if ((currx + 1 < 6) && (visited[currx + 1][curry] == false))
            neighbours.push(std::make_pair(currx + 1, curry));
        if ((curry + 1 < 6) && (visited[currx][curry + 1] == false))
            neighbours.push(std::make_pair(currx, curry + 1));
        if ((currx - 1 >= 0) && (visited[currx - 1][curry] == false))
            neighbours.push(std::make_pair(currx - 1, curry));
        if ((curry - 1 >= 0) && (visited[currx][curry - 1] == false))
            neighbours.push(std::make_pair(currx, curry - 1));

        //std::cout << neighbours.size() << ":" << exit << " at " << currx << "," << curry << std::endl;

        if (neighbours.size())
        {
            int noneighs = neighbours.size();
            int temp = rand() % noneighs;
            while (temp--)
                neighbours.pop();
            int prevx = currx;
            int prevy = curry;
            currx = neighbours.top().first;
            curry = neighbours.top().second;
            while (neighbours.size())
                neighbours.pop();

            if (currx - prevx > 0)
                renderx[currx][curry] = true;
            else if (currx - prevx < 0)
                renderx[prevx][prevy] = true;
            else if (curry - prevy > 0)
                rendery[currx][curry] = true;
            else if (curry - prevy < 0)
                rendery[prevx][prevy] = true;

            sizex2--;

            exit++;
            visited[currx][curry] = true;
            whereareyounow.push(std::make_pair(currx, curry));
        }
        else
        {
            whereareyounow.pop();
            currx = whereareyounow.top().first;
            curry = whereareyounow.top().second;
        }
    }
    /* MAZE GENERATION ALGORITHM ENDS */

    GLfloat vertex_buffer_data[sizex2 * 9];

    int pos = 0;
    for (float y = -3.0; y <= 2.0; y += 1.0)
    {
        for (float x = -3.0; x <= 2.0; x += 1.0)
        {
            //rendery control
            if (!rendery[(int)x + 3][(int)y + 3])
            {
                vertex_buffer_data[pos] = x / 3;
                vertex_buffer_data[++pos] = y / 3;
                vertex_buffer_data[++pos] = 0.0;

                vertex_buffer_data[++pos] = (x + 1.0) / 3;
                vertex_buffer_data[++pos] = y / 3;
                vertex_buffer_data[++pos] = 0.0;

                vertex_buffer_data[++pos] = (x + 1.0) / 3;
                vertex_buffer_data[++pos] = y / 3;
                vertex_buffer_data[++pos] = -1.0;

                ++pos;
            }

            //renderx control
            if (!renderx[(int)x + 3][(int)y + 3])
            {
                vertex_buffer_data[pos] = x / 3;
                vertex_buffer_data[++pos] = y / 3;
                vertex_buffer_data[++pos] = 0.0;

                vertex_buffer_data[++pos] = x / 3;
                vertex_buffer_data[++pos] = (y + 1.0) / 3;
                vertex_buffer_data[++pos] = 0.0;

                vertex_buffer_data[++pos] = x / 3;
                vertex_buffer_data[++pos] = (y + 1.0) / 3;
                vertex_buffer_data[++pos] = -1.0;

                ++pos;
            }
        }
    }

    /*vertex_buffer_data[pos] = 0.8;
    vertex_buffer_data[++pos] = 0.8;
    vertex_buffer_data[++pos] = 0.0;

    vertex_buffer_data[++pos] = 0.8;
    vertex_buffer_data[++pos] = 0.9;
    vertex_buffer_data[++pos] = 0.0;

    vertex_buffer_data[++pos] = 0.9;
    vertex_buffer_data[++pos] = 0.9;
    vertex_buffer_data[++pos] = 0.0;

    vertex_buffer_data[++pos] = 0.9;
    vertex_buffer_data[++pos] = 0.9;
    vertex_buffer_data[++pos] = 0.0;

    vertex_buffer_data[++pos] = 0.8;
    vertex_buffer_data[++pos] = 0.8;
    vertex_buffer_data[++pos] = 0.0;

    vertex_buffer_data[++pos] = 0.9;
    vertex_buffer_data[++pos] = 0.8;
    vertex_buffer_data[++pos] = 0.0;*/

    /*vertex_buffer_data[++pos] = killx - 0.05;
    vertex_buffer_data[++pos] = killy - 0.05;
    vertex_buffer_data[++pos] = 0.0;

    vertex_buffer_data[++pos] = killx - 0.05;
    vertex_buffer_data[++pos] = killy + 0.05;
    vertex_buffer_data[++pos] = 0.0;

    vertex_buffer_data[++pos] = killx + 0.05;
    vertex_buffer_data[++pos] = killy + 0.05;
    vertex_buffer_data[++pos] = 0.0;

    vertex_buffer_data[++pos] = killx + 0.05;
    vertex_buffer_data[++pos] = killy + 0.05;
    vertex_buffer_data[++pos] = 0.0;

    vertex_buffer_data[++pos] = killx - 0.05;
    vertex_buffer_data[++pos] = killy - 0.05;
    vertex_buffer_data[++pos] = 0.0;

    vertex_buffer_data[++pos] = killx + 0.05;
    vertex_buffer_data[++pos] = killy - 0.05;
    vertex_buffer_data[++pos] = 0.0;*/

    //std::cout << sizex2 << ":" << pos << std::endl;

    this->object = create3DObject(GL_TRIANGLES, sizex2 * 3, vertex_buffer_data, color, GL_FILL);
}

void Maze::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Maze::set_position(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
}

void Maze::tick()
{
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}