#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <shader.h>
#include <point.h>
#include <vertex.h>
#include <cstring>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class renderer

{

private:
    void setupRenderer(const char *vertPath, const char *fragPath)
    {
        shader = Shader(vertPath, fragPath);
        glEnable(GL_DEPTH_TEST);
    }
    void setupBufferObjects()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glGenBuffers(1, &EBO);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

        shader.use();
        glBindVertexArray(VAO);
        glUniform1i(glGetUniformLocation(shader.ID, "texEnabled"), 0);
        glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0);
        glUniform1i(glGetUniformLocation(shader.ID, "texture2"), 1);

        // Projection
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(model));

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(model));
    }

public:
    Shader shader;
    float vertices[32];
    unsigned int indices[6] = {

        0, 1, 3,
        1, 2, 3};
    unsigned int VBO, VAO, EBO;
    void init(const char *vertPath, const char *fragPath);
    void drawRect(float verts[32], glm::mat4 trans);
    void drawRectReadable(float x, float y, float width, float height, float r, float g, float b);
    renderer();
    void drawTriangleStrip(vertex verts[], int size, float r, float g, float b);
    void drawTriangle(vertex p1, vertex p2, vertex p3);
    void renderUnsizedArray(float arr[], int len);
    void setViewMat(glm::mat4 view);
    void drawCube(glm::mat4 trans);

    float cubeVertices[288] = {
        -0.5f, -0.5f, -0.5f, 1, 1, 1, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1, 1, 1, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1, 1, 1, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1, 1, 1, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 1, 1, 1, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1, 1, 1, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 1, 1, 1, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1, 1, 1, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1, 1, 1, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1, 1, 1, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 1, 1, 1, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 1, 1, 1, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1, 1, 1, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1, 1, 1, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1, 1, 1, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1, 1, 1, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 1, 1, 1, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1, 1, 1, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1, 1, 1, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1, 1, 1, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1, 1, 1, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1, 1, 1, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1, 1, 1, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1, 1, 1, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 1, 1, 1, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1, 1, 1, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1, 1, 1, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1, 1, 1, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 1, 1, 1, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1, 1, 1, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 1, 1, 1, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1, 1, 1, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1, 1, 1, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1, 1, 1, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1, 1, 1, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1, 1, 1, 0.0f, 1.0f};
};

void renderer::init(const char *vertPath, const char *fragPath)
{
    setupRenderer(vertPath, fragPath);
    setupBufferObjects();
}

void renderer::drawTriangleStrip(vertex vertices[], int size, float r, float g, float b)
{

    glDisable(GL_TEXTURE_2D);
    float verts[8 * size];

    for (int i = 0; i < size; i += 8)
    {
        float *singleVert = vertices[i / 8].getAll();
        memcpy(verts + i, singleVert, 8);
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_DYNAMIC_DRAW);

    shader.use();

    glUniform1i(glGetUniformLocation(shader.ID, "texEnabled"), 0);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, size);
    glEnable(GL_TEXTURE_2D);
}

void renderer::drawTriangle(vertex p1, vertex p2, vertex p3)
{
    glDisable(GL_TEXTURE_2D);
    float verts[24];
    float *x1 = p1.getData();
    float *x2 = p2.getData();
    float *x3 = p3.getData();

    for (int i = 0; i < 8; i++)
    {
        verts[i] = x1[i];
    }
    for (int i = 0; i < 8; i++)
    {
        verts[i + 8] = x2[i];
    }
    for (int i = 0; i < 8; i++)
    {
        verts[i + 16] = x3[i];
    }

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_DYNAMIC_DRAW);

    shader.use();

    glUniform1i(glGetUniformLocation(shader.ID, "texEnabled"), 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glEnable(GL_TEXTURE_2D);
}

void renderer::drawRect(float verts[32], glm::mat4 trans = glm::mat4(1.0f))
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), verts, GL_DYNAMIC_DRAW);

    shader.use();
    glBindVertexArray(VAO);

    glm::mat4 model = glm::mat4(1.0f);
    // model = glm::rotate(model, glm::radians(320.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

    

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glUniform1i(glGetUniformLocation(shader.ID, "texEnabled"), 1);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "trans"), 1, GL_FALSE, glm::value_ptr(trans));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void renderer::drawRectReadable(float x, float y, float width, float height, float r, float g, float b)
{

    // copy vertices to verts
    float verts[] = {
        x + width, y + height, 0.0, r, g, b, 1.0, 1.0,
        x + width, y, 0.0, r, g, b, 1.0, 0.0,
        x, y, 0.0, r, g, b, 0.0, 0.0,
        x, y + height, 0.0, r, g, b, 0.0, 1.0};

    drawRect(verts);
}

void renderer::renderUnsizedArray(float arr[], int len)
{

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, len * sizeof(float), arr, GL_DYNAMIC_DRAW);
    shader.use();
    glBindVertexArray(VAO);

    glUniform1i(glGetUniformLocation(shader.ID, "texEnabled"), 1);

    // glDrawElements(GL_TRIANGLES, len, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, len);
}

void renderer::setViewMat(glm::mat4 view)
{
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));

}

void renderer::drawCube(glm::mat4 mat)
{
    
}

renderer::renderer()
{
}

#endif