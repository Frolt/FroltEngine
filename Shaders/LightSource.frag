#version 410 core

in vec3 Position;
in vec3 Normal;
in vec2 UV;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec4 fadingColor;

void main()
{
    FragColor = vec4(1.0);
}
