#ifndef CIRCLEOBJ
#define CIRCLEOBJ
#define GRAVITY_CONST 0.00000000006674
#include <iostream>
#include <object.h>
#include <point.h>
#include <math.h>
#include <vector>

class circleObject
{
private:
    /* data */
public:
    std::vector<vertex> vertices;
    vertex center;
    int numSegments;
    float radius;
    float xVel, yVel = 0;
    int mass;
    circleObject(int numSegments, int x, int y, float radius, float squish, int mass);
    ~circleObject();
    int transform(float dx, float dy);
    int gravTransform(circleObject c);
    void tick(GLFWwindow *window);
};

circleObject::circleObject(int numSegments, int x, int y, float radius, float squish, int mass) : vertices(numSegments)
{
    float r = .7;
    float g = .7;
    float b = .9;
    this->mass = mass;
    float segsPerQuarter = numSegments / 4;
    for (int i = 0; i < segsPerQuarter; i++)
    {
        float angle = i * (M_PI / (2.0 * segsPerQuarter));
        float dx = radius * std::cos(angle);
        float dy = radius * std::sin(angle);
        vertices[i].setAll(x + dx * squish, y + dy, 0, r, g, b, 1, 1);
    }

    for (int i = segsPerQuarter - 1; i >= 0; i--)
    {
        float angle = i * (M_PI / (2.0 * segsPerQuarter));
        float dx = radius * std::cos(angle);
        float dy = radius * std::sin(angle);
        vertices[segsPerQuarter - 1 - i + segsPerQuarter].setAll(x - dx * squish, y + dy, 0, r, g, b, 1, 1);
    }

    for (int i = 0; i < segsPerQuarter; i++)
    {
        float angle = i * (M_PI / (2.0 * segsPerQuarter));
        float dx = radius * std::cos(angle);
        float dy = radius * std::sin(angle);
        vertices[i + (2 * segsPerQuarter)].setAll(x - dx * squish, y - dy, 0, r, g, b, 1, 1);
    }

    for (int i = segsPerQuarter - 1; i >= 0; i--)
    {
        float angle = i * (M_PI / (2.0 * segsPerQuarter));
        float dx = radius * std::cos(angle);
        float dy = radius * std::sin(angle);
        vertices[segsPerQuarter - 1 - i + (3 * segsPerQuarter)].setAll(x + dx * squish, y - dy, 0, r, g, b, 1, 1);
    }
    center.setAll(x, y, 0, 1, 1, 1, 1, 1);
    this->numSegments = numSegments;
    this->radius = radius;
}

int circleObject::transform(float dx, float dy)
{
    for (int i = 0; i < numSegments; i++)
    {
        vertices[i].setPos(vertices[i].getX() + dx, vertices[i].getY() + dy, vertices[i].getZ());
    }
    center.setPos(center.getX() + dx, center.getY() + dy, center.getZ());
    return 1;
}

void circleObject::tick(GLFWwindow *window)
{
    transform(xVel, yVel);
}

int circleObject::gravTransform(circleObject c)
{
    float xDist = std::abs(center.getX()) - std::abs(c.center.getX());
    float yDist = std::abs(center.getY()) - std::abs(c.center.getY());
    float dist = std::sqrt(xDist * xDist + yDist * yDist);
    float force = GRAVITY_CONST * ((mass * c.mass) / (dist * dist));
    float vel = force/mass;
    float angle = std::atan2(yDist, xDist);
    float dYVel = vel * std::sin(angle);
    float dXVel = vel * std::cos(angle);
    xVel += dXVel;
    yVel += dYVel;
    return 1;
}

circleObject::~circleObject()
{
}

#endif