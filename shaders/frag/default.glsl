#version 330 core
out vec4 FragColor;

in vec4 vertexColor;
in vec2 TexCoord;

uniform sampler2D textureSample;
uniform sampler2D textureSample2;
uniform float fTime;

void main()
{
    FragColor = mix(texture(textureSample, TexCoord), texture(textureSample2, TexCoord), 0.5);
}