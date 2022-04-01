#ifndef PLAYER_H
#define PLAYER_H

#include <object.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <objLoader.h>
#include <AABB.h>


class Player : public object
{
private:
    float velAD = 0, velY = 0, velWS = 0;
    glm::vec3 position;
    glm::vec3 cameraUp;
    float maxSpeed = 0.4;
    glm::vec3 lCamDef = glm::vec3(1.0f);
    // glm::vec3 currentRotation = glm::vec3(1.0f);
    float currentRotation, targetRotation = 0;

    glm::vec3 smoothLinterp(glm::vec3 begin, glm::vec3 end)
    {
        float delX = 0.00001f * (end.x - begin.x);
        std::cout << delX << "Delta X\n";
        begin.x += 0.1f * (end.x - begin.x);
        begin.y += 0.1f * (end.y - begin.y);
        begin.z += 0.1f * (end.z - begin.z);
        return begin;
    }
    float smoothLinterpF(float begin, float end)
    {
        while (begin > 2.0f*M_PI)
        {
            begin -= 2.0f*M_PI;
        }
        while (end > 2.0f*M_PI)
        {
            end -= 2.0f*M_PI;
        }
        
       
        if (abs(end - begin) > M_PI)
        {
            end = -(M_PI*2 - end);
        }
        if (end - begin > 3)
        {
            std::cout << begin << " Is begin, " << end << " Is end.\n";
        }
        begin += 0.1* (end - begin);
        return begin;
    }

public:
    Player(const char *filepath, std::string meshPath) : object(filepath, meshPath)
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

    if (glfwGetKey(window, GLFW_KEY_W) && velWS < maxSpeed)
    {
        velWS += 0.004;
        targetRotation = atan2(camF.x, camF.z);
    }

    else if (glfwGetKey(window, GLFW_KEY_S) && velWS > -maxSpeed)
    {
        velWS -= 0.004;
        targetRotation = atan2(camF.x, camF.z);

    }
    else
    {
        if (velWS > 0)
            velWS -= 0.006;
        if (velWS < 0)
            velWS += 0.006;
        if (abs(velWS) < 0.01)
        {
            velWS = 0;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_A) && velAD > -maxSpeed)
    {
        velAD -= 0.004;
        targetRotation = atan2(camF.x, camF.z);

    }
    else if (glfwGetKey(window, GLFW_KEY_D) && velAD < maxSpeed)
    {
        velAD += 0.004;
        targetRotation = atan2(camF.x, camF.z);

    }
    else
    {
        if (velAD > 0)
            velAD -= 0.006;
        if (velAD < 0)
            velAD += 0.006;
        if (abs(velAD) < 0.01)
        {
            velAD = 0;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) && abs(velY) < 0.005)
    {
        velY += 0.3;
    }
    else if (position.y > 0)
    {
        velY -= 0.50 / 60.0f;
    }

    position.y += velY;
    if (position.y < 0)
    {
        position.y = 0;
        velY = 0;
    }

    float zxScale = sqrt((camF.length() * camF.length()) / (camF.x * camF.x + camF.z * camF.z));
    position -= glm::vec3(camF.x * zxScale * velWS, 0, camF.z * zxScale * velWS);
    position -= glm::normalize(glm::cross(glm::vec3(camF.x * zxScale, 0, camF.z * zxScale), cameraUp)) * velAD;

    trans = glm::translate(trans, position);
    // currentRotation = smoothLinterp(currentRotation, lCamDef);
    currentRotation = smoothLinterpF(currentRotation, targetRotation);

    trans = glm::rotate(trans, currentRotation, glm::vec3(0, 1, 0));
}

glm::vec3 Player::getPosition()
{
    return position;
}

#endif