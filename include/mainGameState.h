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
#include <3bMap.h>
#include <3dPlayer.h>




class gameState : public state
{
private:
    /* data */
    
    float renderRatio;
    Camera camera;
    texture test;
    DMap map;
    std::vector<float> vertices;
    Player player;
    

public:
    gameState(const char *vertPath, const char *fragPath);
    ~gameState();
    virtual void tick(GLFWwindow *window);
    virtual void render();
    void init();
};

void gameState::tick(GLFWwindow *window)
{
  player.tick(window, camera.getCameraF());

    camera.tick(window, player.getPosition());
}

void gameState::render()
{
    
    rend.setViewMat(camera.view);
   
    player.bind();
    rend.renderMesh(&player.getVerts()[0], player.getVerts().size(), player.getTrans());
    
    test.bind();
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::scale(trans, glm::vec3(10.0f));

    rend.renderMesh(&vertices[0], vertices.size(), trans);

    
    // for (int i = 0; i < map.data.size(); i++)
    // {
    //     rend.renderMesh(&map.data[i][0], map.data[i].size(), glm::mat4(1.0f));
    // }

}

void gameState::init()
{
    test.loadTexture("./img/ground.png");
   vertices = loadObj("./data/obj/plane.obj");
    map.loadMap("./data/obj/map/map.stat");
    
}

gameState::gameState(const char *vertPath, const char *fragPath) : state(vertPath, fragPath), player("./img/playerUV.png", "./data/obj/player.obj")
{
    renderRatio = float(glfwGetVideoMode(glfwGetPrimaryMonitor())->height) / float(glfwGetVideoMode(glfwGetPrimaryMonitor())->width);
    

    init();
}

gameState::~gameState()
{
}

#endif