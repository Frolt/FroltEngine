#version 410 core

// Vertex attributes
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

out vec3 Pos;
out vec3 Normal;
out vec2 UV;
out vec3 FragPos;
out vec3 TextureDir;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMat;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    Pos = aPos;
    Normal = normalize(normalMat * aNormal);
    UV = aUV;
    FragPos = vec3(model * vec4(aPos, 1.0));
    TextureDir = aPos;
}
