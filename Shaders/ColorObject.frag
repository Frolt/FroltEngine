#version 410 core

in vec3 Position;
in vec3 Normal;
in vec2 UV;

out vec4 FragColor;

void main()
{
    FragColor = vec4(Normal, 1.0);
}
