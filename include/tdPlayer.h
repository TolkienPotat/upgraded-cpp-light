#ifndef TDPLAYEROBJECT_H
#define TDPLAYEROBJECT_H


#include <iostream>
#include <object.h>

class TDPlayerObject : public object
{
public:
    /* data */
    float xOffset, yOffset = 0;

public:
    virtual void tick(GLFWwindow *window)
    {
        
        if (glfwGetKey(window, GLFW_KEY_W))
        {
            // y += 0.01;
            yOffset += 0.01;
        }
        if (glfwGetKey(window, GLFW_KEY_S))
        {
            // y -= 0.01;
            yOffset -= 0.01;

        }
        if (glfwGetKey(window, GLFW_KEY_D))
        {
            // x += 0.01;
            xOffset += 0.01;

        }
        if (glfwGetKey(window, GLFW_KEY_A))
        {
            // x -= 0.01;
            xOffset -= 0.01;

        }

        

        
    }
    TDPlayerObject(const char *filePath) : object(filePath) {}
};

#endif
