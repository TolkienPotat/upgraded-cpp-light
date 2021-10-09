#ifndef LINE_FUNCTIONS
#define LINE_FUNCTIONS
#include <point.h>

bool ccw(point a, point b, point c)
{
    return ((c.y - a.y)*(b.x-a.x)>(b.y-a.y)*(c.x-a.x));
}

bool intersect(point a, point b, point c, point d)
{
    return((ccw(a, c, d) != ccw(b, c, d)) && (ccw(a, b, c) != ccw(a, b, d)));
}

#endif