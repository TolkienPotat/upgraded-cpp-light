#ifndef TESTSTATE_H
#define TESTSTATE_H
#include <iostream>
#include <state.h>
#include <testObject.h>
#include <blockObject.h>
#include <vector>
#include <algorithm>
#include <glm-master/glm/glm.hpp>

struct square
{
    point v[4];
};

class testState : public state
{
private:
    /* data */
    testObject person;
    blockObject blobject;
    vertex v1, v2, v3, v4;
    point light;
    square box;
    glm::vec4 *shadowMap;
    unsigned int shadowMapID;
    float renderRatio;

public:
    testState(const char *vertPath, const char *fragPath);
    ~testState();
    virtual void tick(GLFWwindow *window);
    virtual void render();
    void init();
    void computeShadows(point light, square s);
};

void testState::tick(GLFWwindow *window)
{

    person.tick(window);
    blobject.tick(window);
    light.set(person.getX(), person.getY());
    computeShadows(light, box);
}

void testState::render()
{
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, shadowMapID);

    rend.drawTriangle(v1, v2, v3);
    rend.drawTriangle(v2, v3, v4);
    rend.render(person);
    rend.render(blobject);
}

void testState::init()
{
    v1.setAll(1, 1, 0, 0.6, 0.5, 0.2, 1, 1);
    v2.setAll(1, -1, 0, 0.6, 0.5, 0.2, 1, 0);
    v3.setAll(-1, 1, 0, 0.6, 0.5, 0.2, 0, 1);
    v4.setAll(-1, -1, 0, 0.6, 0.5, 0.2, 0, 0);

    light.set(-1, 1);
    box.v[0].set(blobject.getX(), blobject.getY());
    box.v[1].set(blobject.getX() + double(blobject.getTexture().width) * blobject.getScale() * renderRatio, blobject.getY());
    box.v[2].set(blobject.getX(), blobject.getY() + double(blobject.getTexture().height) * blobject.getScale());
    box.v[3].set(blobject.getX() + double(blobject.getTexture().width) * blobject.getScale() * renderRatio, blobject.getY() + double(blobject.getTexture().height) * blobject.getScale());

    computeShadows(light, box);
}
void testState::computeShadows(point light, square s)
{
    double slope;
    double maxSlope = 0;
    double minSlope;
    point min;
    point max;
    // square sh;

    for (int i = 0; i < 4; i++)
    {
        point p = s.v[i];
        slope = (light.y - p.y) / (light.x - p.x);

        if (slope > maxSlope || i == 0)
        {
            maxSlope = slope;
            max = p;
        }
        if (slope < minSlope || i == 0)
        {
            minSlope = slope;
            min = p;
        }
    }
    std::cout << std::atan2(min.x - light.x, min.y - light.y) << " " << std::atan2(max.x - light.x, max.y - light.y) << "\n";
    if (std::atan2(min.x - light.x, min.y - light.y) * std::atan2(max.x - light.x, max.y - light.y) < 0)
    {

        for (double i = 0; i < 1080; i++)
        {
            for (double j = 0; j < 1920; j++)
            {
                // Transform X and Y
                double y = 2.0 * (1.0 - i / 1080.0) - 1.0;
                double x = 2.0 * j / 1920.0 - 1.0;
                double slope = (y - light.y) / (x - light.x);
                double s0 = (min.y - max.y) / (min.x - max.x);
                double s1 = (min.y - y) / (min.x - x);
                double s2 = (min.y - light.y) / (min.x - light.y);

                // if (slope < maxSlope && slope > minSlope && ((s1 > s0 > s2) || (s2 > s0 > s1)))
                if ((slope > maxSlope || slope < minSlope) && (((min.y - max.y) * (light.x - min.x) + (max.x - min.x) * (light.y - min.y)) * ((min.y - max.y) * (x - min.x) + (max.x - min.x) * (y - min.y))) < 0)
                {
                    // glm::vec4 v(0.5, 0.5, 0.5, 1.0);
                    double x = 1.0 - 45.0 * std::min(abs(slope - maxSlope) / (maxSlope - minSlope), abs(slope - minSlope) / (maxSlope - minSlope));

                    glm::vec4 v(x, x, x, 1.0);
                    shadowMap[int(i * 1920 + j)] = v;
                }
                else
                {
                    glm::vec4 v(1.0, 1.0, 1.0, 1.0);

                    shadowMap[int(i * 1920 + j)] = v;
                    // std::cout <<x << " " << y << "\n";
                }
            }
        }
    }
    else
    {
        for (double i = 0; i < 1080; i++)
        {
            for (double j = 0; j < 1920; j++)
            {
                // Transform X and Y
                double y = 2.0 * (1.0 - i / 1080.0) - 1.0;
                double x = 2.0 * j / 1920.0 - 1.0;
                double slope = (y - light.y) / (x - light.x);

                // if (slope < maxSlope && slope > minSlope && ((s1 > s0 > s2) || (s2 > s0 > s1)))
                if (slope < maxSlope && slope > minSlope && (((min.y - max.y) * (light.x - min.x) + (max.x - min.x) * (light.y - min.y)) * ((min.y - max.y) * (x - min.x) + (max.x - min.x) * (y - min.y))) < 0)
                {
                    // glm::vec4 v(0.5, 0.5, 0.5, 1.0);
                    double x = 1.0 - 45.0 * std::min(abs(slope - maxSlope) / (maxSlope - minSlope), abs(slope - minSlope) / (maxSlope - minSlope));

                    glm::vec4 v(x, x, x, 1.0);

                    shadowMap[int(i * 1920 + j)] = v;
                }
                else
                {
                    glm::vec4 v(1.0, 1.0, 1.0, 1.0);

                    shadowMap[int(i * 1920 + j)] = v;
                    // std::cout <<x << " " << y << "\n";
                }
            }
        }
    }
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, shadowMapID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 1920, 1080, 0, GL_RGBA, GL_FLOAT, shadowMap);
    glGenerateMipmap(GL_TEXTURE_2D);

    // std::cout << "done\n";
}

testState::testState(const char *vertPath, const char *fragPath) : person("./hero.png"), state(vertPath, fragPath), blobject("./block.png")
{
    renderRatio = float(glfwGetVideoMode(glfwGetPrimaryMonitor())->height) / float(glfwGetVideoMode(glfwGetPrimaryMonitor())->width);
    rend.setRenderRatio(renderRatio);
    shadowMap = new glm::vec4[1920 * 1080];
    glGenTextures(1, &shadowMapID);
    init();
}

testState::~testState()
{
    delete[] shadowMap;
}

#endif