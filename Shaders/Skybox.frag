#version 410 core

out vec4 FragColor;

in vec3 UV;

uniform samplerCube Skybox;

void main()
{    
    FragColor = texture(Skybox, UV);
}