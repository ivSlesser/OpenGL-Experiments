#version 410 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexCoords;
layout (location = 3) in vec3 a_Normals;

out vec3 v_FragmentPosition;
out vec4 v_Color;
out vec2 v_TexCoords;
out vec3 v_Normals;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

void main()
{
    vec4 worldPosition = u_Model * vec4(a_Pos, 1.0);
    gl_Position = u_ViewProjection * worldPosition;
    v_FragmentPosition = worldPosition.xyz;
    v_Color = a_Color;
    v_TexCoords = a_TexCoords;
    v_Normals = a_Normals;
}