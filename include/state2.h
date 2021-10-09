#ifndef TESTSTATE2_H
#define TESTSTATE2_H
#include <iostream>
#include <state.h>
#include <testObject.h>
#include <blockObject.h>
#include <vector>
#include <algorithm>
#include <glm-master/glm/glm.hpp>



class state2 : public state
{
private:
    /* data */
    testObject person;
    blockObject blobject;
    
    
   

public:
    state2(const char *vertPath, const char *fragPath);
    ~state2(){}
    virtual void tick(GLFWwindow *window){
        person.tick(window);
        blobject.tick(window);
    }
    virtual void render(){
        rend.render(person);
        rend.render(blobject);
    }
    void init(){}
    
};

state2::state2(const char *vertPath, const char *fragPath) : person("./hero.png"), state(vertPath, fragPath), blobject("./block.png")
{
    rend.setRenderRatio(float(glfwGetVideoMode(glfwGetPrimaryMonitor())->height) / float(glfwGetVideoMode(glfwGetPrimaryMonitor())->width));
   
    
    init();
    
    
}

#endif