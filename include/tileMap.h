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
    
    std::vector<int> map;
    std::vector<texture> tex;
    std::vector<std::vector<float>> vertices;

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
        for (int i = 0; i < tex.size(); i++)
        {
            std::vector<float> v;
            vertices.push_back(v);
        }
        bakeArrays();
        return 1;
    }

    int bakeArrays()
    {
        for (int i = 0; i < tex.size(); i++)
        {
            for (int j = 0; j < map.size(); j++)
            {
                if (map[j] == i)
                {
                    float x = float(j % width) * tWidth;
                    // std::cout << "X: " << x << "\n";
                    float y = std::floor(float(j) / width) * tHeight;
                    vertices[i].push_back(x + tWidth);
                    vertices[i].push_back(y + tHeight);
                    vertices[i].push_back(0.0);
                    vertices[i].push_back(1);
                    vertices[i].push_back(1);
                    vertices[i].push_back(1);
                    vertices[i].push_back(1);
                    vertices[i].push_back(1);

                    vertices[i].push_back(x + tWidth);
                    vertices[i].push_back(y);
                    vertices[i].push_back(0.0);
                    vertices[i].push_back(1);
                    vertices[i].push_back(1);
                    vertices[i].push_back(1);
                    vertices[i].push_back(1);
                    vertices[i].push_back(0);

                    vertices[i].push_back(x);
                    vertices[i].push_back(y);
                    vertices[i].push_back(0.0);
                    vertices[i].push_back(1);
                    vertices[i].push_back(1);
                    vertices[i].push_back(1);
                    vertices[i].push_back(0);
                    vertices[i].push_back(0);

                    vertices[i].push_back(x + tWidth);
                    vertices[i].push_back(y + tHeight);
                    vertices[i].push_back(0.0);
                    vertices[i].push_back(1);
                    vertices[i].push_back(1);
                    vertices[i].push_back(1);
                    vertices[i].push_back(1);
                    vertices[i].push_back(1);

                    vertices[i].push_back(x);
                    vertices[i].push_back(y + tHeight);
                    vertices[i].push_back(0.0);
                    vertices[i].push_back(1);
                    vertices[i].push_back(1);
                    vertices[i].push_back(1);
                    vertices[i].push_back(0);
                    vertices[i].push_back(1);

                    vertices[i].push_back(x);
                    vertices[i].push_back(y);
                    vertices[i].push_back(0.0);
                    vertices[i].push_back(1);
                    vertices[i].push_back(1);
                    vertices[i].push_back(1);
                    vertices[i].push_back(0);
                    vertices[i].push_back(0);


                }
            }
        std::cout << vertices[i].size() << "\n";
        }
        return 1;
    }
};

#endif