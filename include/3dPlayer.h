#include <object.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef PLAYER_H
#define PLAYER_H

class Player : public object {
    private:
        float velX = 0, velY = 0;
    
    public:
        Player(const char* filepath) : object(filepath) {
            trans = glm::mat4(1.0f);
        };
        ~Player();
        void tick(GLFWwindow* window);
};

void Player::tick(GLFWwindow* window) {
    
}

#endif