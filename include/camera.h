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
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S))
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A))
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D))
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

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
}

Camera::~Camera()
{
}
