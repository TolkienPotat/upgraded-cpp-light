#ifndef TILEMAP
#define TILEMAP
#include <iostream>
#include <fstream>
#include <texture.h>
class tileMap
{

public:
    int width;
    int height;
    float tWidth;
    float tHeight;
    float xOffset = 0;
    float yOffset = 0;
    std::vector<int> map;
    std::vector<texture> tex;

public:
    int loadMap(const char *filePath)
    {

        std::ifstream stream(filePath);

        stream >> width;
        stream >> height;
        stream >> tWidth;
        stream >> tHeight;
        
        std::cout << width << height << tWidth << tHeight << "\n";

        std::string temp;
        stream >> temp;
        std::string s;
        int i = 0;
        // std::getline(stream, s);
        stream >> s;
        while (s != "DATA:")
        {
            std::cout << s << "\n";
            const char *c = s.c_str();
            texture tt;
            tex.push_back(tt);
            tex[i].loadTexture(c);
            // std::getline(stream, s);
            std::cout << tex.size() << "\n";
            stream >> s;
            i++;
        }
        
        int j = 0;
        while (j < width * height)
        {
            std::string t;
            stream >> t;
            map.push_back(std::stoi(t));
            j++;
            
        }

        return 1;
    }
};

#endif