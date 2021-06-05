#include "button.h"
#include "main.h"

Button::Button(float x, float y, color_t color)
{
    srand(time(0));

    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;

    static const GLfloat vertex_buffer_data[] = {
        -0.05f, -0.05f, 0.0f,
        -0.05f, 0.05f, 0.0f,
        0.05f, 0.05f, 0.0f,

        0.05f, 0.05f, 0.0f,
        -0.05f, -0.05f, 0.0f,
        0.05f, -0.05f, 0.0f};

    this->object = create3DObject(GL_TRIANGLES, 2 * 3, vertex_buffer_data, color, GL_FILL);
}

void Button::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

/*void Button::set_position(float x, float y)
{
    this->position = glm::vec3(x, y, 0);
}*/

void Button::tick()
{
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}