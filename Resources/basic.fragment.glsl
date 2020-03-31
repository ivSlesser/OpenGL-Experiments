#version 410 core

out vec4 FragColor;

uniform vec3 pickedColor;

void main()
{
   FragColor = vec4(pickedColor.xyz, 1.0f);
}