#ifndef OBJ_RENDERER
#define OBJ_RENDERER
#include <object.h>
#include <renderer.h>
#include <shader.h>
#include <iostream>
#include <vertex.h>

class objectRenderer
{
private:
    renderer renderman;
    float renderRatio;

public:
    objectRenderer(const char *vertPath, const char *fragPath);
    ~objectRenderer();
    void render(object o);
    void setRenderRatio(float ratio);
    void drawTriangleStrip(point verts[], int size, float r, float g, float b);
    void drawTriangle(vertex p1, vertex p2, vertex p3);
};

objectRenderer::objectRenderer(const char *vertPath, const char *fragPath)

{
    renderman.init(vertPath, fragPath);
    renderRatio = 1;
}

objectRenderer::~objectRenderer()
{
}

void objectRenderer::drawTriangleStrip(point verts[], int size, float r, float g, float b)
{
    renderman.drawTriangleStrip(verts, size, r, g, b);
}

void objectRenderer::drawTriangle(vertex p1, vertex p2, vertex p3)
{
    renderman.drawTriangle(p1, p2, p3);
}

void objectRenderer::setRenderRatio(float ratio)
{
    renderRatio = ratio;
}

void objectRenderer::render(object o)
{

    o.bind();

    renderman.drawRectReadable(o.getX(), o.getY(), float(o.getTexture().width) * o.getScale() * renderRatio, float(o.getTexture().height) * o.getScale(), 1.0f, 1.0f, 1.0f);
}
#endif