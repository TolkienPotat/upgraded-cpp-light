#version 330 core

in vec4 ourColor;
in vec2 texCoord;
layout (origin_upper_left) in vec4 gl_FragCoord;


out vec4 FragColor;

uniform int texEnabled;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    
    
    
    
    if(texEnabled == 1)
    {
        FragColor = texture(texture1, texCoord) * ourColor * texture(texture2, vec2(gl_FragCoord.x/1920.0, gl_FragCoord.y/1080.0));
        // FragColor = texture(texture1, texCoord) * ourColor;
    } else
    {
    // FragColor = ourColor * texture(texture2, vec2(gl_FragCoord.x/1920.0, gl_FragCoord.y/1080.0));
        FragColor = ourColor;

    }
    
    
    
}