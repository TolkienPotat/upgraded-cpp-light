#ifndef VERTEX_H
#define VERTEX_H

class vertex
{
private:
    /* data */
    float *data = new float[8];

public:
    vertex(/* args */);
    ~vertex();
    void setPos(float x, float y, float z)
    {
            data[0] = x;
            data[1] = y;
            data[2] = z;
    }
    void setColor(float r, float g, float b)
    {
            data[3] = r;
            data[4] = g;
            data[5] = b;
    }
    void setTexCoords(float s, float t)
    {
            data[6] = s;
            data[7] = t;
    }
    float *getData()
    {
        return data;
    }

    float getX()
    {
        return data[0];
    }
    float getY()
    {
        return data[1];
    }
    float getZ()
    {
        return data[2];
    }
    void setAll(float x, float y, float z, float r, float g, float b, float s, float t)
    {
        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = r;
        data[4] = g;
        data[5] = b;
        data[6] = s;
        data[7] = t;
        
    }
    float* getAll()
    {
        return data;
    }
};

vertex::vertex(/* args */)
{
}

vertex::~vertex()
{
}

#endif