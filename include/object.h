#ifndef OBJECT_H
#define OBJECT_H

#include <texture.h>
#include <renderer.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class object
{
protected:
    /* data */
    texture t;
    float x = 0, y = 0, z = 0;
    float scale = 1.0f / 64.0f;
    int width, height;
    glm::mat4 trans;
    float vertices[32];


public:
    object(const char *filePath);
    ~object();
    void tick();
    void bind();
    texture getTexture();
    float getX();
    float getY();
    float getScale();
    float* getVerts();
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

    vertices[0] = float(width)*scale/2.0;
    vertices[1] = float(height)*scale/2.0;
    vertices[2] = 0;
    vertices[3] = 1;
    vertices[4] = 1;
    vertices[5] = 1;
    vertices[6] = 1;
    vertices[7] = 1;

    vertices[8] = float(width)*scale/2.0;
    vertices[9] = -float(height)*scale/2.0;
    vertices[10] = 0;
    vertices[11] = 1;
    vertices[12] = 1;
    vertices[13] = 1;
    vertices[14] = 1;
    vertices[15] = 0;

    vertices[16] = -float(width)*scale/2.0;
    vertices[17] = -float(height)*scale/2.0;
    vertices[18] = 0;
    vertices[19] = 1;
    vertices[20] = 1;
    vertices[21] = 1;
    vertices[22] = 0;
    vertices[23] = 0;

    vertices[24] = -float(width)*scale/2.0;
    vertices[25] = float(height)*scale/2.0;
    vertices[26] = 0;
    vertices[27] = 1;
    vertices[28] = 1;
    vertices[29] = 1;
    vertices[30] = 0;
    vertices[31] = 1;



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

float* object::getVerts()
{
    return vertices;
}
#endif