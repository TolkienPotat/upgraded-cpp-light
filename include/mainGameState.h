#ifndef GAMESTATE
#define GAMESTATE
#include <iostream>
#include <state.h>
#include <circle.h>
#include <vector>
#include <algorithm>
#include <PlayerObject.h>
#include <tileMap.h>
#include <tdPlayer.h>
#include <camera.h>
#include <texture.h>
#include <objLoader.h>





class gameState : public state
{
private:
    /* data */
    
    float renderRatio;
    // PlayerObject player;
    TDPlayerObject player;
    tileMap map;
    Camera camera;
    texture test;
    float verts[32]{-100.0f, 0, -100.0f, 1, 1, 1, 0, 0,
                    -100.0f, 0, 100.0f, 1, 1, 1, 0, 1,
                    100.0f, 0, 100.0f, 1, 1, 1, 1, 1,
                    100.0f, 0, -100.0f, 1, 1, 1, 1, 0};
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
    player.tick(window);
  

    camera.tick(window);
}

void gameState::render()
{
    // rend.drawMap(map);
    rend.setViewMat(camera.view);
    rend.render(player);

    // rend.drawRect(glm::mat4(1.0f), verts);
                rend.renderMesh(&vertices[0], vertices.size(), glm::mat4(1.0f));

}

void gameState::init()
{
    map.loadMap("./map.rmap");
    test.loadTexture("./sand1.png");
   vertices = loadObj("./data/obj/shaefile.obj");
   
   std::cout << vertices.size();
    
}

gameState::gameState(const char *vertPath, const char *fragPath) : state(vertPath, fragPath), player("./img/block.png")
{
    renderRatio = float(glfwGetVideoMode(glfwGetPrimaryMonitor())->height) / float(glfwGetVideoMode(glfwGetPrimaryMonitor())->width);
    

    init();
}

gameState::~gameState()
{
}

#endif