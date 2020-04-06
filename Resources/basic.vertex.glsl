#version 410 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexCoords;

out vec4 v_Color;
out vec2 v_TexCoords;

uniform mat4 u_Model;

void main()
{
    gl_Position = u_Model * vec4(a_Pos, 1.0);
    v_Color = a_Color;
    v_TexCoords = a_TexCoords;
}