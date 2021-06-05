#include "main.h"
#include "timer.h"
#include "maze.h"
#include "amogh.h"
#include "impos.h"
#include "hud.h"
#include "button.h"
#include "coin.h"
#include "end.h"
#include <unistd.h>

using namespace std;

GLMatrices Matrices;
GLuint programID;
GLFWwindow *window;

Maze maze1;
Amogh char1;
Impos impos1;
Hud hud1;
Button killbutton;
Button powbutton;
Button lastexit;
Button killrep, powrep, lastrep;
Coin up1, up2, down1, down2;
End end1;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float amoghx = -0.833333, amoghy = -0.833333, imposx, imposy, killx, killy, powx, powy, up1x, up1y, up2x, up2y, down1x, down1y, down2x, down2y;
int lives = 5, endval = 0;
bool imposdead = false, gotpow = false, canquit = false, up1bool = false, up2bool = false, down1bool = false, down2bool = false;

Timer t60(1.0 / 6);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programID);

    Matrices.view = glm::lookAt(glm::vec3(-1, -1, 45), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 VP = Matrices.projection * Matrices.view;

    glm::mat4 MVP;
    hud1 = Hud(lives);
    hud1.draw(VP);
    maze1.draw(VP);
    char1.draw(VP);
    impos1.draw(VP);
    if (imposdead == false)
    {
        killbutton.draw(VP);
        killrep.draw(VP);
    }
    if (gotpow == false)
    {
        powbutton.draw(VP);
        powrep.draw(VP);
    }
    if (canquit == true)
        lastexit.draw(VP);
    lastrep.draw(VP);
    if (gotpow == true)
    {
        if (up1bool == false)
            up1.draw(VP);
        if (up2bool == false)
            up2.draw(VP);
        if (down1bool == false)
            down1.draw(VP);
        if (down2bool == false)
            down2.draw(VP);
    }

    if (endval == 2)
    {
        end1 = End(false);
        end1.draw(VP);
    }
    if (endval == 1)
    {
        end1 = End(true);
        end1.draw(VP);
    }
}

void tick_input(GLFWwindow *window)
{
    int left = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);

    //convert -0.83-0.83 to 0-5
    int tempx = (int)((amoghx * 3.0) + 3.0);
    int tempy = (int)((amoghy * 3.0) + 3.0);
    //check if wall exists
    if (left)
    {
        if (maze1.renderx[tempx][tempy])
            amoghx -= 0.333333;
    }
    else if (right)
    {
        if (maze1.renderx[tempx + 1][tempy])
            if (amoghx < 0.8)
                amoghx += 0.333333;
    }
    else if (up)
    {
        if (maze1.rendery[tempx][tempy + 1])
            if (amoghy < 0.8)
                amoghy += 0.333333;
    }
    else if (down)
    {
        if (maze1.rendery[tempx][tempy])
            amoghy -= 0.333333;
    }

    char1.set_position(amoghx, amoghy);
}

void initGL(GLFWwindow *window, int width, int height)
{
    /* Objects should be created before any other gl function and shaders */
    imposx = (float)(rand() % 6);
    imposy = 5.0 - imposx;

    imposx = (imposx - 2.5) / 3;
    imposy = (imposy - 2.5) / 3;

    killx = (float)(rand() % 6);
    killy = 5.0 - killx;

    killx = (killx - 2.5) / 3;
    killy = (killy - 2.5) / 3;

    killx = (float)(rand() % 6);
    killy = 5.0 - killx;

    killx = (killx - 2.5) / 3;
    killy = (killy - 2.5) / 3;

    powx = (float)(rand() % 6);
    powy = 5.0 - powx;

    powx = (powx - 2.5) / 3;
    powy = (powy - 2.5) / 3;

    up1x = (float)(rand() % 6);
    up1x = (up1x - 2.5) / 3;
    up1y = (float)(rand() % 6);
    up1y = (up1y - 2.5) / 3;
    up2x = (float)(rand() % 6);
    up2x = (up2x - 2.5) / 3;
    up2y = (float)(rand() % 6);
    up2y = (up2y - 2.5) / 3;
    down1x = (float)(rand() % 6);
    down1x = (down1x - 2.5) / 3;
    down1y = (float)(rand() % 6);
    down1y = (down1y - 2.5) / 3;
    down2x = (float)(rand() % 6);
    down2x = (down2x - 2.5) / 3;
    down2y = (float)(rand() % 6);
    down2y = (down2y - 2.5) / 3;

    hud1 = Hud(lives);
    end1 = End(false);
    maze1 = Maze(0, 0, COLOR_GREEN);
    char1 = Amogh(amoghx, amoghy);
    impos1 = Impos(imposx, imposy);
    killbutton = Button(killx, killy, COLOR_RED);
    powbutton = Button(powx, powy, COLOR_YELLOW);
    lastexit = Button(0.833333, 0.833333, COLOR_GREEN);

    killrep = Button(0.533333, 1.09, COLOR_RED);
    powrep = Button(0.7, 1.09, COLOR_YELLOW);
    lastrep = Button(0.866666, 1.09, COLOR_GREEN);

    up1 = Coin(up1x, up1y, true);
    up2 = Coin(up2x, up2y, true);
    down1 = Coin(down1x, down1y, false);
    down2 = Coin(down2x, down2y, false);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("../source/shaders/shader.vert", "../source/shaders/shader.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    reshapeWindow(window, width, height);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

void tick()
{
    if (imposdead == true && gotpow == true)
        canquit = true;

    if (amoghx > 0.8 && amoghy > 0.8 && canquit == true)
    {
        endval = 1;
    }

    if ((abs(amoghx - imposx) < 0.05) && (abs(amoghy - imposy) < 0.05))
    {
        endval = 2;
    }

    if ((abs(amoghx - killx) < 0.05) && (abs(amoghy - killy) < 0.05))
    {
        imposx = -1.5;
        imposy = -1.5;
        impos1.set_position(imposx, imposy);
        imposdead = true;
    }

    if ((abs(amoghx - powx) < 0.05) && (abs(amoghy - powy) < 0.05))
        gotpow = true;

    if ((abs(amoghx - up1x) < 0.05) && (abs(amoghy - up1y) < 0.05) && up1bool == false && gotpow == true)
    {
        lives++;
        up1bool = true;
    }

    if ((abs(amoghx - up2x) < 0.05) && (abs(amoghy - up2y) < 0.05) && up2bool == false && gotpow == true)
    {
        lives++;
        up2bool = true;
    }

    if ((abs(amoghx - down1x) < 0.05) && (abs(amoghy - down1y) < 0.05) && down1bool == false && gotpow == true)
    {
        lives--;
        down1bool = true;
    }

    if ((abs(amoghx - down2x) < 0.05) && (abs(amoghy - down2y) < 0.05) && down2bool == false && gotpow == true)
    {
        lives--;
        down2bool = true;
    }

    if (imposdead == false)
    {
        int tempx = (int)((imposx * 3.0) + 3.0);
        int tempy = (int)((imposy * 3.0) + 3.0);
        //check if wall exists
        int choice = rand() % 4;
        switch (choice)
        {
        case 0:
            if (maze1.renderx[tempx][tempy])
                imposx -= 0.333333;
            break;
        case 1:
            if (maze1.renderx[tempx + 1][tempy])
                if (imposx < 0.8)
                    imposx += 0.333333;
            break;
        case 2:
            if (maze1.rendery[tempx][tempy + 1])
                if (imposy < 0.8)
                    imposy += 0.333333;
            break;
        case 3:
            if (maze1.rendery[tempx][tempy])
                imposy -= 0.333333;
            break;
        }
        impos1.set_position(imposx, imposy);
    }
}

int main(int argc, char **argv)
{
    srand(time(0));
    int width = 600;
    int height = 720;
    //imposdead = false;

    window = initGLFW(width, height);

    initGL(window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window))
    {
        // Process timers

        if (t60.processTick())
        {
            // 60 fps
            // OpenGL Draw commands
            draw();
            tick();

            //if (endval > 0)
            //    break;
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

void reset_screen()
{
    float top = screen_center_y + 1.20 / screen_zoom;
    float bottom = screen_center_y - 1.00 / screen_zoom;
    float left = screen_center_x - 1.00 / screen_zoom;
    float right = screen_center_x + 1.00 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}