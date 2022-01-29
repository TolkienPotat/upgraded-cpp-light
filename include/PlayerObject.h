#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

// #include <texture.h>
// #include <renderer.h>
#include <iostream>
#include <object.h>

class PlayerObject : public object
{
private:
    /* data */
    float velY = 0;
    float velX = 0;
    float jumpVel = 0.11;
    float gravAcc = 0.005;

public:
    virtual void tick(GLFWwindow *window)
    {
        
        if (glfwGetKey(window, GLFW_KEY_PAGE_UP))
        {
            jumpVel += 0.01;
            std::cout << "Jump: " << jumpVel << "\n";
        }
        else if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN))
        {
            jumpVel -= 0.01;
            std::cout << "Jump: " << jumpVel << "\n";
        }

        

        if (y != -1)
        {
            velY -= gravAcc;
        }
        else
        {
            velY = 0;
        }
        if (velX > 0)
        {
            velX -= 0.001;
        }
        else if (velX < 0)
        {
            velX += 0.001;
        }
        if (velX < 0.001 & velX > -0.001) velX = 0;

        if (glfwGetKey(window, GLFW_KEY_SPACE) && velY == 0)
        {
            velY += jumpVel;
        }

        if (glfwGetKey(window, GLFW_KEY_A))
            velX -= 0.005;
        if (glfwGetKey(window, GLFW_KEY_D))
            velX += 0.005;

        x += velX;
        y += velY;
        if (y < -1)
            y = -1;
    }
    PlayerObject(const char *filePath) : object(filePath) {}
};

#endif
