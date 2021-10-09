#ifndef BLOCKOBJ
#define BLOCKOBJ

#include <iostream>
#include <object.h>

class blockObject : public object
{
private:
    /* data */
public:
    blockObject(const char* filePath);
    ~blockObject();
    virtual void tick(GLFWwindow *window)
    {

    }
};

blockObject::blockObject(const char* filePath) : object(filePath)
{
}

blockObject::~blockObject()
{
}


#endif