#version 410 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_TexCoords;
layout (location = 2) in vec3 a_Normals;

out vec3 v_FragmentPosition;
out vec2 v_TexCoords;
out vec3 v_Normals;
out float v_Visibility;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_ViewProjection;
uniform bool u_ApplyFog;
uniform float u_Density;
uniform float u_Gradient;
uniform float u_Time;
uniform float u_DeltaTime;

uniform vec4 u_Wave0;
uniform vec4 u_Wave1;
uniform vec4 u_Wave2;

const float PI = 3.1415926535897932384626433832795;

vec3 GerstnerWave (vec4 wave, vec3 p, inout vec3 tangent, inout vec3 binormal);

void main()
{
    vec3 p = a_Pos;
    vec3 tangent = vec3(1.0, 0.0, 0.0);
    vec3 binormal = vec3(0.0, 0.0, 1.0);

    p += GerstnerWave(u_Wave0, a_Pos, tangent, binormal);
    p += GerstnerWave(u_Wave1, a_Pos, tangent, binormal);
    p += GerstnerWave(u_Wave2, a_Pos, tangent, binormal);

    vec4 worldPosition = u_Model * vec4(p, 1.0);

    gl_Position = u_ViewProjection * worldPosition;
    v_FragmentPosition = worldPosition.xyz;

    v_TexCoords = a_TexCoords;
    v_Normals = normalize(cross(binormal, tangent));

    // Fog -----------------------------------------------------------------
    v_Visibility = 1.0;
    if (u_ApplyFog) {
        vec4 posRelativeToCam = u_View * worldPosition;
        float distance = length(posRelativeToCam.xyz);
        v_Visibility = exp(-pow((distance * u_Density), u_Gradient));
        v_Visibility = clamp(v_Visibility, 0.0, 1.0);
    }
}

vec3 GerstnerWave (vec4 wave, vec3 p, inout vec3 tangent, inout vec3 binormal)
{
    float steepness = wave.z;

    float k = 2 * PI / wave.w;// Wavelength
    float c = sqrt(9.8 / k);// Phase speed
    vec2 d = normalize(wave.xy);// Normalized wave direction
    float f = k * (dot(d, p.xz) - c * u_Time);// Wave slope
    float a = steepness / k; // Amplitude

    tangent += vec3(
    -d.x * d.x * (steepness * sin(f)),
    d.x * (steepness * cos(f)),
    -d.x * d.y * (steepness * sin(f))
    );

    binormal += vec3(
    -d.x * d.y * (steepness * sin(f)),
    d.y * (steepness * cos(f)),
    -d.y * d.y * (steepness * sin(f))
    );

    return vec3(
    d.x * (a * cos(f)),
    a * sin(f),
    d.y * (a * cos(f)) + sin(u_Time)
    );
}