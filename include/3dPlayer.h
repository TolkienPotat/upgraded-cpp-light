#include <object.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <objLoader.h>

#ifndef PLAYER_H
#define PLAYER_H

class Player : public object
{
private:
    float velAD = 0, velY = 0, velWS = 0;
    glm::vec3 position;
    glm::vec3 cameraUp;

public:
    Player(const char *filepath, std::string meshPath) : object(filepath)
    {
        trans = glm::mat4(1.0f);
        vertices = loadObj(meshPath);
        position = glm::vec3(x, y, z);
        cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    };
    ~Player() {}
    void tick(GLFWwindow *window, glm::vec3 camF);
    glm::vec3 getPosition();
};

void Player::tick(GLFWwindow *window, glm::vec3 camF)
{

    trans = glm::mat4(1.0f);

    if (glfwGetKey(window, GLFW_KEY_W) && velWS < 1)
    {
        velWS += 0.001;
    }

    else if (glfwGetKey(window, GLFW_KEY_S))
    {
        velWS -= 0.001;
    }
    else
    {
        if (velWS > 0)
            velWS -= 0.001;
        if (velWS < 0)
            velWS += 0.001;
        if (abs(velWS) < 0.01)
        {
            velWS = 0;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_A))
    {
        velAD -= 0.001;
    }
    else if (glfwGetKey(window, GLFW_KEY_D))
    {
        velAD += 0.001;
    }
    else
    {
        if (velAD > 0)
            velAD -= 0.001;
        if (velAD < 0)
            velAD += 0.001;
        if (abs(velAD) < 0.01)
        {
            velAD = 0;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) && abs(velY) < 0.005)
    {
        velY += 0.2;
    }
    else if (position.y > 0)
    {
        velY -= 0.005;
    }

    position.y += velY;
    if (position.y < 0)
    {
        position.y = 0;
        velY = 0;
    }
    position -= glm::vec3(camF.x * velWS, 0, camF.z * velWS);
    position -= glm::normalize(glm::cross(glm::vec3(camF.x, 0, camF.z), cameraUp)) * velAD;

    trans = glm::translate(trans, position);
}

glm::vec3 Player::getPosition()
{
    return position;
}

#endif