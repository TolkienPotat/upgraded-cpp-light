#ifndef OBJ_LOADER
#define OBJ_LOADER
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

struct coord
{
    float x, y, z = 0;
};
struct tCoord
{
    float x, y = 0;
};
struct vNorm
{
    float x, y, z = 0;
};

    std::vector<coord> coordVec;
    std::vector<tCoord> tCoordVec;
    std::vector<vNorm> vNormVec;

std::vector<float> loadObj(std::string path)
{
    std::vector<float> res;
    std::string line;
    std::ifstream file(path);
    std::getline(file, line);
    std::getline(file, line);
    file >> line;
    while(line == "o")
    {
    std::getline(file, line);

    file >> line;
    while (line == "v")
    {
        file >> line;
        coord c;
        c.x = std::stof(line);
        file >> line;
        c.y = std::stof(line);
        file >> line;
        c.z = std::stof(line);
        coordVec.push_back(c);
        file >> line;
    }
    while (line == "vt")
    {
        file >> line;
        tCoord c;
        c.x = std::stof(line);
        file >> line;
        c.y = std::stof(line);
        tCoordVec.push_back(c);
        file >> line;
    }
    while (line == "vn")
    {
        file >> line;
        vNorm c;
        c.x = std::stof(line);
        file >> line;
        c.y = std::stof(line);
        file >> line;
        c.z = std::stof(line);
        vNormVec.push_back(c);
        file >> line;
    }
    std::getline(file, line);

    file >> line;
    while (line == "f")
    {
        for (int i = 0; i < 3; i++)
        {
        file >> line;
        std::replace(line.begin(), line.end(), '/', ' ');
        std::stringstream in(line);
        int pos;
        in >> pos;
        pos -=1;
        res.push_back(coordVec[pos].x);
        res.push_back(coordVec[pos].y);
        res.push_back(coordVec[pos].z);

        res.push_back(1.0f);
        res.push_back(1.0f);
        res.push_back(1.0f);

        in >> pos;
        pos -=1;
        res.push_back(tCoordVec[pos].x);
        res.push_back(tCoordVec[pos].y);
        in >> pos;
        
        }
        file >> line;

    }
    }
    // std::cout << line << "\n";
    vNormVec.clear();
    tCoordVec.clear();
    coordVec.clear();
    return res;
}
#endif