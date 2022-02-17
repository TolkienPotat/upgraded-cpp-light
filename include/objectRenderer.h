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
    void renderPlayer(object o);
    void setRenderRatio(float ratio);
    void drawTriangleStrip(vertex verts[], int size, float r, float g, float b);
    void drawTriangle(vertex p1, vertex p2, vertex p3);
    void drawCircle(circleObject c);
    void drawMap(tileMap m);
    void setViewMat(glm::mat4 view);
    void drawRect(glm::mat4 trans, float verts[32]);
    void renderMesh(float verts[], int size, glm::mat4 model);
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

void objectRenderer::renderPlayer(object o)
{

}

void objectRenderer::render(object o)
{

    o.bind();
    renderman.drawRect(o.getVerts(), o.getTrans());
    // renderman.drawRectReadable(o.getX(), o.getY(), float(o.getTexture().width) * o.getScale() * renderRatio, float(o.getTexture().height) * o.getScale(), 1.0f, 1.0f, 1.0f);
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

    

    for (int i = 0; i < m.vertices.size(); i++)
    {
        m.tex[i].bind();
        renderman.renderUnsizedArray(&m.vertices[i][0], m.vertices[i].size(), glm::mat4(1.0f));
    }
}

void objectRenderer::setViewMat(glm::mat4 view)
{
    renderman.setViewMat(view);
}

void objectRenderer::drawRect(glm::mat4 trans, float verts[32])
{
    renderman.drawRect(verts, trans);
}

void objectRenderer::renderMesh(float verts[], int size, glm::mat4 model)
{

}

#endif