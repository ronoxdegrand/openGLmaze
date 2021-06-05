#include "amogh.h"
#include "main.h"

Amogh::Amogh(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;

    static const GLfloat vertex_buffer_data[] = {
        -1.0f, -0.5f, -0.5f, //lower bag
        -0.5f, -0.5f, -0.5f,
        -1.0f, 0.5f, -0.5f,

        -0.5f, -0.5f, -0.5f, //upper bag
        -1.0f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,

        -0.5f, -1.0f, -0.5f, //lower amogh
        0.5f, -1.0f, -0.5f,
        -0.5f, 1.0f, -0.5f,

        0.5f, -1.0f, -0.5f, //upper amogh
        -0.5f, 1.0f, -0.5f,
        0.5f, 1.0f, -0.5f,

        -0.25f, 0.25f, -0.45f, //lower goggles
        0.75f, 0.25f, -0.45f,
        -0.25f, 0.75f, -0.45f,

        0.75f, 0.25f, -0.45f, //upper goggles
        -0.25f, 0.75f, -0.45f,
        0.75f, 0.75f, -0.45f};

    static const GLfloat g_color_buffer_data[] = {
        0.195f, 0.448f, 0.659f,
        0.195f, 0.448f, 0.659f,
        0.195f, 0.448f, 0.659f,

        0.195f, 0.448f, 0.659f,
        0.195f, 0.448f, 0.659f,
        0.195f, 0.448f, 0.659f,

        0.195f, 0.548f, 0.900f,
        0.195f, 0.548f, 0.900f,
        0.195f, 0.548f, 0.900f,

        0.195f, 0.548f, 0.900f,
        0.195f, 0.548f, 0.900f,
        0.195f, 0.548f, 0.900f,

        0.014f, 0.184f, 0.576f,
        0.771f, 0.328f, 0.970f,
        0.406f, 0.615f, 0.116f,

        0.676f, 0.977f, 0.133f,
        0.971f, 0.572f, 0.833f,
        0.140f, 0.616f, 0.489f};

    this->object = create3DObject(GL_TRIANGLES, 6 * 3, vertex_buffer_data, g_color_buffer_data, GL_FILL);
}

void Amogh::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);

    glm::mat4 scale = glm::scale(glm::vec3(0.1, 0.1, 1));

    Matrices.model *= (translate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Amogh::set_position(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
}

void Amogh::tick()
{
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
