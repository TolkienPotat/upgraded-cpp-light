#ifndef OBJ_LOADER
#define OBJ_LOADER
#include <iostream>
#include <vector>
#include <fstream>

std::vector<float> loadObj(std::string path)
{
    std::string line;
    std::ifstream file(path);
    std::getline(file, line);
    file >> line;
    std::cout << line;


}
#endif