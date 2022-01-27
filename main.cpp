#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <shader.h>
#include <renderer.h>
#include <objectRenderer.h>
#include <cstdlib>
#include <time.h>

#include <GravitySimulation.h>
// #include <audioTest.h>

GLFWwindow *window;
int wWidth = 1920;
int wHeight = 1080;
float wRatio = float(wHeight) / float(wWidth);

void tick(GLFWwindow *window)
{
}

void terminate()
{

    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    wWidth = width;
    wHeight = height;
    wRatio = float(wHeight) / float(wWidth);
}

void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void init(GLFWwindow *window)
{

    if (!window)
    {
        // Window or OpenGL context creation failed
        std::cout << "Failed to create Window"
                  << "\n";
    }

    glfwSetErrorCallback(error_callback);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    gladLoadGL();

    glViewport(0, 0, 1920, 1080);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetKeyCallback(window, key_callback);
    glfwSwapInterval(1);
}

int main()
{

    if (!glfwInit()) 
    {
        // Initialization failed
        std::cout << "Init Failed"
                  << "\n";
    }

    const GLFWvidmode *vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    wWidth = vidMode->width;
    wHeight = vidMode->height;

    window = glfwCreateWindow(wWidth, wHeight, "My Title", glfwGetPrimaryMonitor(), NULL);
    init(window);

    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD); // this is default
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    gravSim state("./vertexShader.vs", "./fragmentShader.fs");
    // audioState state("./vertexShader.vs", "./fragmentShader.fs");

    

    double delta = 0;
    double last = 0;
    double time1 = 0;
    double updateTime = 1.0 / 60.0;
    double numberOfTicks = 0;

    glClearColor(0.2, 0.2, 0.2, 0.2);
    srand(time(NULL));
    point vertexes[5000];
    int numVertexesDrawn = 0;

    int cooldown = 0;
    
    while (!glfwWindowShouldClose(window))
    {
        cooldown--;
        glClear(GL_COLOR_BUFFER_BIT);
        // Keep running

        glfwPollEvents();

        time1 = glfwGetTime();
        delta += time1 - last;
        if (delta > updateTime)
        {
            //tick
            tick(window);
            state.tick(window);
            if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            else
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }

            delta -= updateTime;

            numberOfTicks++;
        }
        last = time1;

        state.render();

        glfwSwapBuffers(window);
    }
    glfwDestroyWindow(window);
    terminate();
}