#version 410 core

out vec4 FragColor;

uniform vec3 u_PickedColor;

void main()
{
   FragColor = vec4(u_PickedColor.xyz, 1.0f);
}