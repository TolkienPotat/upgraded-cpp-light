#ifndef AABB_I
#define AABB_I

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class AABB
{
private:
    /* data */

    glm::vec3 v1;
    glm::vec3 v2;

public:
    AABB(glm::vec3 greatest, glm::vec3 lowest);
    ~AABB();
    int collidesWith(AABB obj);
    static AABB genFromObj(std::vector<float> object, int repeat);
    void offset(glm::vec3 translate);
};

AABB::AABB(glm::vec3 greatest, glm::vec3 lowest)
{
    v1 = lowest;
    v2 = greatest;
}

AABB::~AABB()
{
}

int AABB::collidesWith(AABB obj)
{

    if ((v1.x < obj.v1.x < v2.x || v1.x < obj.v2.x < v2.x || obj.v1.x < v1.x < obj.v2.x || obj.v1.x < v2.x < obj.v2.x) && (v1.y < obj.v1.y < v2.y || v1.y < obj.v2.y < v2.y || obj.v1.y < v1.y < obj.v2.y || obj.v1.y < v2.y < obj.v2.y) && (v1.z < obj.v1.z < v2.z || v1.z < obj.v2.z < v2.z || obj.v1.z < v1.z < obj.v2.z || obj.v1.z < v2.z < obj.v2.z))
        return 1;
    return 0;
}

AABB AABB::genFromObj(std::vector<float> object, int repeat/*usually 8*/)
{

    glm::vec3 v1;
    glm::vec3 v2;
    float leastPoint = 0;
    float greatestPoint = 0;

    for(int i = 0; i < object.size(); i+= repeat)
    {
        if(i == 0 || object[i] > greatestPoint) greatestPoint = object[i];
        if(i == 0 || object[i] < leastPoint) leastPoint = object[i];
    }
    v1.x = leastPoint;
    v2.x = greatestPoint;
    greatestPoint, leastPoint = 0;
    for(int i = 1; i < object.size(); i+= repeat)
    {
        if(i == 1 || object[i] > greatestPoint) greatestPoint = object[i];
        if(i == 1 || object[i] < leastPoint) leastPoint = object[i];
    }
    v1.y = leastPoint;
    v2.y = greatestPoint;
    greatestPoint, leastPoint = 0;
    for(int i = 2; i < object.size(); i+= repeat)
    {
        if(i == 2 || object[i] > greatestPoint) greatestPoint = object[i];
        if(i == 2 || object[i] < leastPoint) leastPoint = object[i];
    }
    v1.z = leastPoint;
    v2.z = greatestPoint;
    return AABB(v2, v1);
}

void AABB::offset(glm::vec3 translate)
{

    v1 += translate;
    v2 += translate;

}

#endif