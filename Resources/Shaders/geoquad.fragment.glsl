#version 410 core

out vec4 FragColor;

in vec4 g_Color;

void main()
{
   FragColor = g_Color;
}