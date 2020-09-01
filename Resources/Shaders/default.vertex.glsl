#version 410 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_TexCoords;
layout (location = 2) in vec3 a_Normals;

out vec3 v_FragmentPosition;
out vec2 v_TexCoords;
out vec3 v_Normals;
out float v_Visibility;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

uniform float u_Density;
uniform float u_Gradient;

void main()
{
    vec4 worldPosition = u_Model * vec4(a_Pos, 1.0);
    gl_Position = u_ViewProjection * worldPosition;
    v_FragmentPosition = worldPosition.xyz;
    v_TexCoords = a_TexCoords;
    v_Normals = (u_Model * vec4(a_Normals, 1.0)).xyz;

    float distance = length(posRelativeToCam.xyz);
    v_Visibility = exp(-pow((distance * u_Density), u_Gradient));
    v_Visibility = clamp(v_Visibility, 0.0, 1.0);
}