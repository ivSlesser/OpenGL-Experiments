#version 410 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexCoords;
layout (location = 3) in vec3 a_Normals;
layout (location = 4) in float a_MatIndex;
layout (location = 5) in mat4 a_Model;

out vec3 v_FragmentPosition;
out vec4 v_Color;
out vec2 v_TexCoords;
out vec3 v_Normals;
out float v_MatIndex;

uniform mat4 u_ViewProjection;

void main()
{
    vec4 worldPosition = a_Model * vec4(a_Pos, 1.0);
    gl_Position = u_ViewProjection * worldPosition;
    v_FragmentPosition = worldPosition.xyz;
    v_Color = a_Color;
    v_TexCoords = a_TexCoords;
    v_Normals = (a_Model * vec4(a_Normals, 1.0)).xyz;
    v_MatIndex = a_MatIndex;
}