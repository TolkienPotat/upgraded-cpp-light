#ifndef AUDIOSIM
#define AUDIOSIM
#include <iostream>
#include <state.h>
#include <circle.h>
#include <vector>
#include <algorithm>
#include <SFML/Audio.hpp>




class audioState : public state
{
private:
    /* data */
    
    float renderRatio;
    sf::Music music;    
    

public:
    audioState(const char *vertPath, const char *fragPath);
    ~audioState();
    virtual void tick(GLFWwindow *window);
    virtual void render();
    void init();
};

void audioState::tick(GLFWwindow *window)
{
    
}

void audioState::render()
{
    
    
   
}

void audioState::init()
{
    if (!music.openFromFile("./test.wav")) std::cout << "Loading music didn't work\n";
    music.play();
    
}

audioState::audioState(const char *vertPath, const char *fragPath) : state(vertPath, fragPath)
{
    renderRatio = float(glfwGetVideoMode(glfwGetPrimaryMonitor())->height) / float(glfwGetVideoMode(glfwGetPrimaryMonitor())->width);
    rend.setRenderRatio(renderRatio);
    std::cout << renderRatio << "\n";
    

    init();
}

audioState::~audioState()
{
}

#endif