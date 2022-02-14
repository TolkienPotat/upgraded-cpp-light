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





class gameState : public state
{
private:
    /* data */
    
    float renderRatio;
    // PlayerObject player;
    TDPlayerObject player;
    tileMap map;
    Camera camera;
    

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
    map.xOffset = player.xOffset;
    map.yOffset = player.yOffset;

    camera.tick(window);
}

void gameState::render()
{
    // rend.drawMap(map);
    rend.setViewMat(camera.view);
    rend.render(player);
    
   
}

void gameState::init()
{
    map.loadMap("./map.rmap");
    
}

gameState::gameState(const char *vertPath, const char *fragPath) : state(vertPath, fragPath), player("./img/traveller.png")
{
    renderRatio = float(glfwGetVideoMode(glfwGetPrimaryMonitor())->height) / float(glfwGetVideoMode(glfwGetPrimaryMonitor())->width);
    rend.setRenderRatio(renderRatio);
    std::cout << renderRatio << "\n";
    

    init();
}

gameState::~gameState()
{
}

#endif