#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class Camera
{
private:
    double mouseX = 1920 / 2;
    double mouseY = 1080 / 2;
    float lastMouseX = mouseX;
    float lastMouseY = mouseY;

    const float sensitivity = 0.1f;

    bool firstMouse = true;

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float cameraSpeed = 0.25f;
    float yaw = 0;
    float pitch = 0;
    glm::vec3 direction;

    float wVel = 0;
    float sVel = 0;
    float aVel = 0;
    float dVel = 0;

public:
    glm::mat4 view;
    Camera(/* args */);
    ~Camera();
    void tick(GLFWwindow *window);
};

Camera::Camera(/* args */)
{
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::tick(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_W))
    {
        wVel += 0.05;
        cameraPos += cameraSpeed * wVel * cameraFront;
    }
    else 
    {
        wVel = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_S))
    {
        sVel += 0.05;

        cameraPos -= cameraSpeed * sVel * cameraFront;
    }
    else 
    {
        sVel = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_A))
    {
        aVel += 0.05;
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * aVel;
    }
    else 
    {
        aVel = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_D))
    {
        dVel += 0.05;
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * dVel;
    }
    else 
    {
        dVel = 0;
    }

    if (firstMouse) // initially set to true
    {
        lastMouseX = mouseX;
        lastMouseY = mouseY;
        firstMouse = false;
    }

    glfwGetCursorPos(window, &mouseX, &mouseY);
    float dX = mouseX - lastMouseX;
    float dY = lastMouseY - mouseY;

    dX *= sensitivity;
    dY *= sensitivity;

    yaw += dX;
    pitch += dY;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch)); // Note that we convert the angle to radians first
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);

    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    lastMouseX = mouseX;
    lastMouseY = mouseY;

    if (wVel > 0) wVel -=0.02;
    if (sVel > 0) sVel -=0.02;
    if (aVel > 0) aVel -=0.02;
    if (dVel > 0) dVel -=0.02;

}

Camera::~Camera()
{
}
