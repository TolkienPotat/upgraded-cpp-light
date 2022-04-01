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
    glm::vec3 velA = glm::vec3(0.0f);
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
        while (begin > 2.0f * M_PI)
        {
            begin -= 2.0f * M_PI;
        }
        while (end > 2.0f * M_PI)
        {
            end -= 2.0f * M_PI;
        }

        if (abs(end - begin) > M_PI)
        {
            end = -(M_PI * 2 - end);
        }
        if (end - begin > 3)
        {
            std::cout << begin << " Is begin, " << end << " Is end.\n";
        }
        begin += 0.1 * (end - begin);
        return begin;
    }

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
    float wsD, adD = 0;
    bool keyDown = false;
    if (glfwGetKey(window, GLFW_KEY_W) && glm::length(velA) < maxSpeed)
    {
        wsD += 0.004;
        targetRotation = atan2(camF.x, camF.z);
        keyDown = true;
    }

    else if (glfwGetKey(window, GLFW_KEY_S) && glm::length(velA) < maxSpeed)
    {
        wsD -= 0.004;
        targetRotation = atan2(camF.x, camF.z);
        keyDown = true;
    }

    if (glfwGetKey(window, GLFW_KEY_A) && glm::length(velA) < maxSpeed)
    {
        adD -= 0.004;
        targetRotation = atan2(camF.x, camF.z);
        keyDown = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_D) && glm::length(velA) < maxSpeed)
    {
        adD += 0.004;
        targetRotation = atan2(camF.x, camF.z);
        keyDown = true;
    }
    if (!keyDown)
    {
        // if (velA.z > 0)
        //     velA.z -= 0.002*;
        // if (velA.z < 0)
        //     velA.z += 0.002;
        if (abs(velA.z) < 0.01 && abs(velA.x) < 0.01)
        {
            velA.z = 0;
            velA.x = 0;
        }
        // if (velA.x > 0)
        //     velA.x -= 0.002;
        // if (velA.x < 0)
        //     velA.x += 0.002;
        
        velA.x *= 0.97;
        velA.z *= 0.97;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) && abs(velA.y) < 0.005)
    {
        velA.y += 0.3;
    }
    else if (position.y > 0)
    {
        velA.y -= 0.50 / 60.0f;
    }

    position.y += velA.y;
    if (position.y < 0)
    {
        position.y = 0;
        velA.y = 0;
    }
    float zxScale = sqrt((glm::length(camF) * glm::length(camF)) / (camF.x * camF.x + camF.z * camF.z));
    velA.x -= camF.x * zxScale * wsD;
    velA.z -= camF.z * zxScale * wsD;
    velA -= glm::normalize(glm::cross(glm::vec3(camF.x * zxScale, 0, camF.z * zxScale), cameraUp)) * adD;
    // position -= glm::vec3(camF.x * zxScale * velWS, 0, camF.z * zxScale * velWS);
    // position -= glm::normalize(glm::cross(glm::vec3(camF.x * zxScale, 0, camF.z * zxScale), cameraUp)) * velAD;
    if (velA.length() > 0.5)
        std::cout << "X: " << velA.x << ", Len: " << velA.length() << ", Z: " << velA.z << "\n";
    position += velA;
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