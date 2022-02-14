#ifndef TDPLAYEROBJECT_H
#define TDPLAYEROBJECT_H

#include <iostream>
#include <object.h>


class TDPlayerObject : public object
{
public:
    /* data */
    float xOffset, yOffset = 0;
    float dX, dY, dZ = 0;

public:
    virtual void tick(GLFWwindow *window)
    {

        if (glfwGetKey(window, GLFW_KEY_W) && dY < 0.1)
        {
            dY += 0.01;
            // yOffset += 0.01;
        }
        if (glfwGetKey(window, GLFW_KEY_S) && dY > -0.1)
        {
            dY -= 0.01;
            // yOffset -= 0.01;
        }
        if (glfwGetKey(window, GLFW_KEY_D) && dX < 0.1)
        {
            dX += 0.01;
            // xOffset += 0.01;
        }
        
        if (glfwGetKey(window, GLFW_KEY_A) && dX > -0.1)
        {
            dX -= 0.01;
            // xOffset -= 0.01;
        }
        x += dX;
        y += dY;
        trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(x, y, z));
        // trans = glm::rotate(trans, x, glm::vec3(0.0, 0.0, 1.0));
        if (dX > 0) dX -= 0.01;
        if (dX < 0) dX += 0.01;
        if (dY > 0) dY -= 0.01;
        if (dY < 0) dY += 0.01;
        if (dX < 0.01 && dX > -0.01) dX = 0;
        if (dY < 0.01 && dY > -0.01) dY = 0;

        // std::cout << dX << " " << dY << "\n";
    }
    TDPlayerObject(const char *filePath) : object(filePath)
    {
        trans = glm::mat4(1.0f);
    }
};

#endif
