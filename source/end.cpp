#include "end.h"
#include "main.h"

End::End(bool eh)
{
    this->position = glm::vec3(0, 0, 0);
    this->rotation = 0;
    speed = 1;

    if (eh == false)
    {
        static const GLfloat vertex_buffer_data[] = {
            -1.0f, -1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,

            -1.0f, 1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,

            0.0f, -0.25f, 1.0f,
            -0.25f, 0.25f, 1.0f,
            0.25f, 0.25f, 1.0f};

        static const GLfloat g_color_buffer_data[] = {
            0.576f, 0.569f, 1.0f,
            0.576f, 0.569f, 1.0f,
            0.576f, 0.569f, 1.0f,

            0.576f, 0.569f, 1.0f,
            0.576f, 0.569f, 1.0f,
            0.576f, 0.569f, 1.0f,

            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f};

        this->object = create3DObject(GL_TRIANGLES, 3 * 3, vertex_buffer_data, g_color_buffer_data, GL_FILL);
    }
    else
    {
        static const GLfloat vertex_buffer_data[] = {
            -1.0f, -1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,

            -1.0f, 1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,

            -0.25f, -0.25f, 1.0f,
            0.0f, 0.25f, 1.0f,
            0.25f, -0.25f, 1.0f};

        static const GLfloat g_color_buffer_data[] = {
            1.0f, 0.545f, 0.353f,
            1.0f, 0.545f, 0.353f,
            1.0f, 0.545f, 0.353f,

            1.0f, 0.545f, 0.353f,
            1.0f, 0.545f, 0.353f,
            1.0f, 0.545f, 0.353f,

            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f};

        this->object = create3DObject(GL_TRIANGLES, 3 * 3, vertex_buffer_data, g_color_buffer_data, GL_FILL);
    }
}

void End::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}