#ifndef OBJ_RENDERER
#define OBJ_RENDERER
#include <object.h>
#include <renderer.h>
#include <shader.h>
#include <iostream>
#include <vertex.h>
#include <circle.h>
#include <tileMap.h>

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
    void drawTriangleStrip(vertex verts[], int size, float r, float g, float b);
    void drawTriangle(vertex p1, vertex p2, vertex p3);
    void drawCircle(circleObject c);
    void drawMap(tileMap m);
};

objectRenderer::objectRenderer(const char *vertPath, const char *fragPath)

{
    renderman.init(vertPath, fragPath);
    renderRatio = 1;
}

objectRenderer::~objectRenderer()
{
}

void objectRenderer::drawTriangleStrip(vertex verts[], int size, float r, float g, float b)
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

void objectRenderer::drawCircle(circleObject c)
{

    for (int i = 0; i < c.numSegments - 1; i++)
    {
        renderman.drawTriangle(c.center, c.vertices[i], c.vertices[i + 1]);
    }
    renderman.drawTriangle(c.center, c.vertices[c.numSegments - 1], c.vertices[0]);
}

void objectRenderer::drawMap(tileMap m)
{

    for (int i = 0; i < m.map.size(); i++)
    {
        m.tex[m.map[i]].bind();
        renderman.drawRectReadable(i % m.width * m.tWidth - m.xOffset, std::floor(float(i)/m.width) * m.tHeight - m.yOffset, m.tWidth, m.tHeight, 1, 1, 1);
    }

}

#endif