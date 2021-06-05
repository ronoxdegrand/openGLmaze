#include "coin.h"
#include "main.h"

Coin::Coin(float x, float y, bool upordown)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;

    if (upordown == false)
    {
        static const GLfloat vertex_buffer_data[] = {
            0.0f, -0.05f, 0.0f,
            -0.05f, 0.05f, 0.0f,
            0.05f, 0.05f, 0.0f};

        static const GLfloat g_color_buffer_data[] = {
            0.576f, 0.569f, 1.0f,
            0.576f, 0.569f, 1.0f,
            0.576f, 0.569f, 1.0f};

        this->object = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, g_color_buffer_data, GL_FILL);
    }
    else
    {
        static const GLfloat vertex_buffer_data[] = {
            -0.05f, -0.05f, 0.0f,
            0.0f, 0.05f, 0.0f,
            0.05f, -0.05f, 0.0f};

        static const GLfloat g_color_buffer_data[] = {
            1.0f, 0.545f, 0.353f,
            1.0f, 0.545f, 0.353f,
            1.0f, 0.545f, 0.353f};

        this->object = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, g_color_buffer_data, GL_FILL);
    }
}

void Coin::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

/*void Coin::set_position(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
}*/

void Coin::tick()
{
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}