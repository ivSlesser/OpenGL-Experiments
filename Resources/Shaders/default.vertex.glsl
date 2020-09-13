#version 410 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_TexCoords;
layout (location = 2) in vec3 a_Normals;

out vec3 v_FragmentPosition;
out vec2 v_TexCoords;
out vec3 v_Normals;
out float v_Visibility;

layout (std140) uniform General {
    vec3 SkyColor;
    float AmbientStrength;
    vec3 SunColor;
    float SpecularStrength;
    vec3 SunPosition;
    float Time;
    float DeltaTime;
} general;

layout (std140) uniform Camera {
    mat4 View;
    mat4 Projection;
    mat4 ViewProjection;
    vec3 Position;
    float Near;
    vec3 Front;
    float Far;
    vec3 Up;
} camera;

uniform mat4 u_Model;
uniform bool u_ApplyFog;
uniform float u_Density;
uniform float u_Gradient;

void main()
{
    vec4 worldPosition = u_Model * vec4(a_Pos, 1.0);
    gl_Position = camera.ViewProjection * worldPosition;
    v_FragmentPosition = worldPosition.xyz;
    v_TexCoords = a_TexCoords;
    v_Normals = (u_Model * vec4(a_Normals, 1.0)).xyz;

    // Fog -----------------------------------------------------------------
    v_Visibility = 1.0f;
    if (u_ApplyFog) {
        vec4 posRelativeToCam = camera.View * worldPosition;
        float distance = length(posRelativeToCam.xyz);
        v_Visibility = exp(-pow((distance * u_Density), u_Gradient));
        v_Visibility = clamp(v_Visibility, 0.0, 1.0);
    }
}