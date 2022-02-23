#ifndef GAMESTATE
#define GAMESTATE
#include <iostream>
#include <state.h>
#include <circle.h>
#include <vector>
#include <algorithm>
#include <tileMap.h>
#include <camera.h>
#include <texture.h>
#include <objLoader.h>





class gameState : public state
{
private:
    /* data */
    
    float renderRatio;
    tileMap map;
    Camera camera;
    texture test;
    
    std::vector<float> vertices;
    

public:
    gameState(const char *vertPath, const char *fragPath);
    ~gameState();
    virtual void tick(GLFWwindow *window);
    virtual void render();
    void init();
};

void gameState::tick(GLFWwindow *window)
{
  

    camera.tick(window);
}

void gameState::render()
{
    
    rend.setViewMat(camera.view);

    
                rend.renderMesh(&vertices[0], vertices.size(), glm::mat4(1.0f));

}

void gameState::init()
{
    map.loadMap("./map.rmap");
    test.loadTexture("./sand1.png");
   vertices = loadObj("./data/obj/shaefile.obj");
   
   std::cout << vertices.size();
    
}

gameState::gameState(const char *vertPath, const char *fragPath) : state(vertPath, fragPath)
{
    renderRatio = float(glfwGetVideoMode(glfwGetPrimaryMonitor())->height) / float(glfwGetVideoMode(glfwGetPrimaryMonitor())->width);
    

    init();
}

gameState::~gameState()
{
}

#endif