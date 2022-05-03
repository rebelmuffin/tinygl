#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec2 aTexCoord;

out vec4 vertexColor;
out vec2 TexCoord;
uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * transform * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
    vertexColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    TexCoord = aTexCoord;
}