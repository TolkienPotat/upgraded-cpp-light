#ifndef GRAVSIM
#define GRAVSIM
#include <iostream>
#include <state.h>
#include <circle.h>
#include <vector>
#include <algorithm>

struct square
{
    point v[4];
};

class gravSim : public state
{
private:
    /* data */
    
    float renderRatio;
    std::vector<circleObject> stat;
    std::vector<circleObject> circles;
    int cooldown = 0;
    bool mouseDown = false;
    double cDownX;
    double cDownY;

public:
    gravSim(const char *vertPath, const char *fragPath);
    ~gravSim();
    virtual void tick(GLFWwindow *window);
    virtual void render();
    void init();
};

void gravSim::tick(GLFWwindow *window)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) && cooldown == 0 && !mouseDown)
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        y = 1 - (2 * (1 - (y / 1080)));
        x = 1 - (2 * (x / 1920));
        mouseDown = true;
        cDownX = x;
        cDownY = y;
        
        cooldown = 30;
    }
    if (mouseDown && !glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        y = 1 - (2 * (1 - (y / 1080)));
        x = 1 - (2 * (x / 1920));
        circleObject c(100, -x, -y, 0.15, float(glfwGetVideoMode(glfwGetPrimaryMonitor())->height) / float(glfwGetVideoMode(glfwGetPrimaryMonitor())->width), 100000, 0.2, 0.2, 0.7);
        //    c.xVel, c.yVel = 0;
        c.xVel = (x - cDownX)/100.0;
        c.yVel = (y - cDownY)/100.0;
        circles.push_back(c);
        
        mouseDown = false;

    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) && cooldown == 0)
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        y = 1 - (2 * (1 - (y / 1080)));
        x = 1 - (2 * (x / 1920));
        circleObject c(100, -x, -y, 0.20, float(glfwGetVideoMode(glfwGetPrimaryMonitor())->height) / float(glfwGetVideoMode(glfwGetPrimaryMonitor())->width), 500000, 0.7, 0.2, 0.2);
        c.xVel, c.yVel = 0;
        stat.push_back(c);
        cooldown = 30;
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_5) && cooldown == 0)
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        y = 1 - (2 * (1 - (y / 1080)));
        x = 1 - (2 * (x / 1920));
        circleObject c(100, -x, -y, 0.20, float(glfwGetVideoMode(glfwGetPrimaryMonitor())->height) / float(glfwGetVideoMode(glfwGetPrimaryMonitor())->width), 500000, 0.2, 0.7, 0.2);
        c.xVel, c.yVel = 0;
        c.mass = -c.mass;
        stat.push_back(c);
        
        cooldown = 30;
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE))
    {
        circles.clear();
        stat.clear();
    }

    for (int i = 0; i < circles.size(); i++)
    {
        circles[i].tick(window);
    }

    for (int i = 0; i < circles.size(); i++)
    {
       
        for (int j = 0; j < circles.size(); j++)
        {
            if (j == i)
                continue;

            circles[i].gravTransform(circles[j]);
        }

        for (int j = 0; j < stat.size(); j++)
        {
            circles[i].gravTransform(stat[j]);
        }
    }

    if (cooldown > 0)
        cooldown--;
}

void gravSim::render()
{
    
    for (int i = 0; i < circles.size(); i++)
    {
        rend.drawCircle(circles[i]);
    }
    for (int i = 0; i < stat.size(); i++)
    {
        rend.drawCircle(stat[i]);
    }
   
}

void gravSim::init()
{
    
}

gravSim::gravSim(const char *vertPath, const char *fragPath) : state(vertPath, fragPath)
{
    renderRatio = float(glfwGetVideoMode(glfwGetPrimaryMonitor())->height) / float(glfwGetVideoMode(glfwGetPrimaryMonitor())->width);
    rend.setRenderRatio(renderRatio);
    std::cout << renderRatio << "\n";
    

    init();
}

gravSim::~gravSim()
{
}

#endif