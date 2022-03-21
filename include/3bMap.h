#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <sstream>
#include <objLoader.h>
#include <texture.h>


class DMap
{

public:
std::vector<std::vector<float>> data;
std::vector<texture> textures;
glm::mat4 model = glm::mat4(1.0f);

int loadMap(std::string path)
{
    std::ifstream file(path);
    std::string line;
    file >> line;
    while (line == "s")
    {
        file >> line;
        texture t;
        t.loadTexture(line.c_str());
        textures.push_back(t);
        file >> line;
        std::vector<float> temp = loadObj(line);
        std::cout << temp.size() << "b\n";
        data.push_back(temp);
        file >> line;
    }
    return 1;

}

std::vector<float> getRender(int r)
{
    textures[r].bind();
    return data[r];
}

};