#include <iostream>
#include <point.h>

int main()
{

    point light;
    light.set(-1, 1);
    point min;
    min.set(0,0);
    point max;
    max.set(0.5,0.5);
    double x = 0.5;
    double y = 0.5;
    double s0 = (min.y - max.y) / (min.x - max.x);
    // double z = ((min.y - max.y) * (light.x - min.x) + (max.x - min.x) * (light.y - min.y)) * ((min.y - max.y) * (x - min.x) + (max.x - min.x) * (y - min.y));
    double s1 = (min.y - y)/(min.x - x);
    double s2 = (min.y - light.y)/(min.x - light.y);
    if ((s1 > s0 > s2) || (s2 > s0 > s1))
    {
        std::cout << "Success!\n";
    }
    else{
        // std::cout << z << "\n";
    }
}