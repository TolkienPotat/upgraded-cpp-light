#ifndef POINT_H
#define POINT_H

class point
{
private:
    /* data */
public:
    double x, y;
    point();
    void set(double x1, double y1);
    ~point();
};

point::point()
{
   
}
void point::set(double x1, double y1)
{
    x = x1;
    y = y1;
}
point::~point()
{
}

#endif

