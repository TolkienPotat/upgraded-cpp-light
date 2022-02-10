#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 trans;

out vec4 ourColor;
out vec2 texCoord;

#define M_PI 3.1415926535897932384626433832795
void main()
{

 

gl_Position = projection * view * model * trans * vec4(aPos, 1.0);
// gl_Position = vec4(aPos, 1.0);
ourColor = vec4(aColor, 1.0);
texCoord = aTexCoord;


}