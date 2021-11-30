#ifndef TESTSTATE_H
#define TESTSTATE_H
#include <iostream>
#include <state.h>
#include <circle.h>
#include <vector>
#include <algorithm>
#include <glm-master/glm/glm.hpp>

struct square
{
    point v[4];
};

class testState2 : public state
{
private:
    /* data */
    circleObject circle;
    circleObject circle2;
    float renderRatio;

public:
    testState2(const char *vertPath, const char *fragPath);
    ~testState2();
    virtual void tick(GLFWwindow *window);
    virtual void render();
    void init();
    void computeShadows(point light, square s);
};

void testState2::tick(GLFWwindow *window)
{
   
    
    // if (circle.center.getX() + renderRatio * circle.radius > 1 || circle.center.getX() - renderRatio * circle.radius < -1)
    //     circle.xVel = -circle.xVel;

    // if (circle.center.getY() + circle.radius > 1 || circle.center.getY() - circle.radius < -1)
    //     circle.yVel = -circle.yVel;
    circle.tick(window);
    circle.gravTransform(circle2);
    std::cout << circle.center.getX() << " " << circle.center.getY() << "\n";
}

void testState2::render()
{
    rend.drawCircle(circle);
    rend.drawCircle(circle2);
}

void testState2::init()
{
    circle.xVel = 0.0;
    circle.yVel = 0.0;
}

testState2::testState2(const char *vertPath, const char *fragPath) : state(vertPath, fragPath), circle(1000, 0.5, 0.5, 0.25, float(glfwGetVideoMode(glfwGetPrimaryMonitor())->height) / float(glfwGetVideoMode(glfwGetPrimaryMonitor())->width), 1), circle2(1000, 0, 0, 0.25, float(glfwGetVideoMode(glfwGetPrimaryMonitor())->height) / float(glfwGetVideoMode(glfwGetPrimaryMonitor())->width), 1)
{
    renderRatio = float(glfwGetVideoMode(glfwGetPrimaryMonitor())->height) / float(glfwGetVideoMode(glfwGetPrimaryMonitor())->width);
    rend.setRenderRatio(renderRatio);
    std::cout << renderRatio << "\n";

    init();
}

testState2::~testState2()
{
}

#endif