#ifndef VERTEX_H
#define VERTEX_H
#ifndef VERTEX_NULLVALUE
#define VERTEX_NULLVALUE 2
#endif

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
        if (x != VERTEX_NULLVALUE)
            data[0] = x;
        if (y != VERTEX_NULLVALUE)
            data[1] = y;
        if (z != VERTEX_NULLVALUE)
            data[2] = z;
    }
    void setColor(float r, float g, float b)
    {
        if (r != VERTEX_NULLVALUE)
            data[3] = r;
        if (g != VERTEX_NULLVALUE)
            data[4] = g;
        if (b != VERTEX_NULLVALUE)
            data[5] = b;
    }
    void setTexCoords(float s, float t)
    {
        if (s != VERTEX_NULLVALUE)
            data[6] = s;
        if (t != VERTEX_NULLVALUE)
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