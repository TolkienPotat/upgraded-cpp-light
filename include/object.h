#ifndef OBJECT_H
#define OBJECT_H

#include <texture.h>
#include <renderer.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class object
{
protected:
    /* data */
    texture t;
    float x = 0, y = 0, z = 0;
    float scale = 1.0f / 64.0f;
    int width, height;
    glm::mat4 trans;
    std::vector<float> vertices;


public:
    object(const char *filePath);
    ~object();
    void tick();
    void bind();
    texture getTexture();
    float getX();
    float getY();
    float getScale();
    std::vector<float> getVerts();
    glm::mat4 getTrans();
    virtual void tick(GLFWwindow *window);
};

object::object(const char *filePath)
{
    t.loadTexture(filePath);
    width = t.width;
    height = t.height;
    std::cout << "created texture"
              << "\n";

    



}



void object::tick(GLFWwindow *window)
{

    std::cout << "Default Object Tick\n";
}



void object::bind()
{
    t.bind();
}

object::~object()
{
}

texture object::getTexture()
{
    return t;
}

float object::getX()
{
    return x;
}

float object::getY()
{
    return y;
}

float object::getScale()
{
    return scale;
}

glm::mat4 object::getTrans()
{
    return trans;
}

std::vector<float> object::getVerts()
{
    
    return vertices;
}
#endif