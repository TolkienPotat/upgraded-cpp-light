#ifndef MAP_I
#define MAP_I

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <sstream>
#include <objLoader.h>
#include <texture.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class DMap
{

public:
std::vector<std::vector<float>> data;
std::vector<texture> textures;
std::vector<glm::mat4> transform;
std::vector<std::string> texturePaths;


int loadMap(std::string path)
{
    std::ifstream file(path);
    std::string line;
    file >> line;
    while (line == "s")
    {
        file >> line;
        texture t;
        texturePaths.push_back(line);
        t.loadTexture(line.c_str());
        textures.push_back(t);
        file >> line;
        std::vector<float> temp = loadObj(line);
        std::cout << temp.size() << "b\n";
        data.push_back(temp);
        file >> line;
        glm::vec3 tVec;
        tVec.x = std::stof(line);
        file >> line;
        tVec.y = std::stof(line);
        file >> line;
        tVec.z = std::stof(line);
        transform.push_back(glm::translate(glm::mat4(1.0f), tVec));
        file >> line;
    }
    return 1;

}

glm::mat4 getRender(int r)
{
    textures[r].bind();
    return transform[r];
}

void reloadTextures()
{
    for (int i = 0; i < textures.size(); i++)
    {
        textures[i].loadTexture(texturePaths[i].c_str());
    }
}

};

#endif