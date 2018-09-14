#version 410 core

in vec3 Pos;
in vec3 Normal;
in vec2 UV;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float interpolation;

out vec4 FragColor;

void main()
{
    FragColor = mix(texture(texture0, UV), texture(texture1, UV), interpolation);
}
