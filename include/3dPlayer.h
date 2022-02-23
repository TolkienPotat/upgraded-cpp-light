#include <object.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <objLoader.h>
#include <GLFW/glfw3.h>

#ifndef PLAYER_H
#define PLAYER_H

class Player : public object {
    private:
        float velX = 0, velY = 0;
        std::vector<float> verts;

    public:
        Player(const char* texPath, const char* objPath) : object(texPath) {
            trans = glm::mat4(1.0f);

            verts = loadObj(objPath);
        };
        ~Player();
        void tick(GLFWwindow* window);
};

void Player::tick(GLFWwindow* window) {
    
}

#endif