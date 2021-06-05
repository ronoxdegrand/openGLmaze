#include "hud.h"
#include "main.h"

Hud::Hud(int eh)
{
    this->position = glm::vec3(0, 0.2, 0);
    this->rotation = 0;
    //this->lives = eh;
    speed = 1;

    GLfloat vertex_buffer_data[(eh + 2) * 9];
    GLfloat g_color_buffer_data[(eh + 2) * 9];
    int pos = 0;

    for (float i = 0; i <= eh - 1; i += 1.0)
    {
        vertex_buffer_data[pos] = (i / 7.5) - 0.95;
        g_color_buffer_data[pos] = 1.0f;
        vertex_buffer_data[++pos] = 0.95;
        g_color_buffer_data[pos] = 0.0f;
        vertex_buffer_data[++pos] = 0.2;
        g_color_buffer_data[pos] = 0.0f;

        vertex_buffer_data[++pos] = (i / 7.5) - 0.9;
        g_color_buffer_data[pos] = 0.25f;
        vertex_buffer_data[++pos] = 0.85;
        g_color_buffer_data[pos] = 0.0f;
        vertex_buffer_data[++pos] = 0.2;
        g_color_buffer_data[pos] = 0.0f;

        vertex_buffer_data[++pos] = (i / 7.5) - 0.85;
        g_color_buffer_data[pos] = 1.0f;
        vertex_buffer_data[++pos] = 0.95;
        g_color_buffer_data[pos] = 0.0f;
        vertex_buffer_data[++pos] = 0.2;
        g_color_buffer_data[pos] = 0.0f;

        ++pos;
    }

    vertex_buffer_data[pos] = -1.0;
    g_color_buffer_data[pos] = 1.0f;
    vertex_buffer_data[++pos] = 0.8;
    g_color_buffer_data[pos] = 1.0f;
    vertex_buffer_data[++pos] = -0.5;
    g_color_buffer_data[pos] = 1.0f;

    vertex_buffer_data[++pos] = 1.0;
    g_color_buffer_data[pos] = 1.0f;
    vertex_buffer_data[++pos] = 0.8;
    g_color_buffer_data[pos] = 1.0f;
    vertex_buffer_data[++pos] = -0.5;
    g_color_buffer_data[pos] = 1.0f;

    vertex_buffer_data[++pos] = -1.0;
    g_color_buffer_data[pos] = 1.0f;
    vertex_buffer_data[++pos] = 1.0;
    g_color_buffer_data[pos] = 1.0f;
    vertex_buffer_data[++pos] = -0.5;
    g_color_buffer_data[pos] = 1.0f;

    vertex_buffer_data[++pos] = -1.0;
    g_color_buffer_data[pos] = 1.0f;
    vertex_buffer_data[++pos] = 1.0;
    g_color_buffer_data[pos] = 1.0f;
    vertex_buffer_data[++pos] = -0.5;
    g_color_buffer_data[pos] = 1.0f;

    vertex_buffer_data[++pos] = 1.0;
    g_color_buffer_data[pos] = 1.0f;
    vertex_buffer_data[++pos] = 1.0;
    g_color_buffer_data[pos] = 1.0f;
    vertex_buffer_data[++pos] = -0.5;
    g_color_buffer_data[pos] = 1.0f;

    vertex_buffer_data[++pos] = 1.0;
    g_color_buffer_data[pos] = 1.0f;
    vertex_buffer_data[++pos] = 0.8;
    g_color_buffer_data[pos] = 1.0f;
    vertex_buffer_data[++pos] = -0.5;
    g_color_buffer_data[pos] = 1.0f;

    this->object = create3DObject(GL_TRIANGLES, (eh + 2) * 3, vertex_buffer_data, g_color_buffer_data, GL_FILL);
}

void Hud::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);

    //glm::mat4 scale = glm::scale(glm::vec3(0.1, 0.1, 1));

    Matrices.model *= (translate); // * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

/*void Hud::set_lives(float x)
{
    this->lives = x;
}*/