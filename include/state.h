#ifndef STATE_H
#define STATE_H
#include <iostream>
#include <objectRenderer.h>

class state
{
private:
    /* data */
protected:
    objectRenderer rend;
    int wWidth = 640;
    int wHeight = 480;
    float wRatio = float(wHeight) / float(wWidth);

public:
    state(const char *vertPath, const char *fragPath);
    virtual ~state();
    virtual void tick(GLFWwindow *window){}
    virtual void render(){}
    void setWindowRatio(float ratio);
    void setScreenDimensions(int width, int height);
};

state::state(const char *vertPath, const char *fragPath) : rend(vertPath, fragPath)
{
}

state::~state()
{
}

void state::setWindowRatio(float ratio)
{
    wRatio = ratio;
}
void state::setScreenDimensions(int width, int height)
{
    wWidth = width;
    wHeight = height;

}

#endif