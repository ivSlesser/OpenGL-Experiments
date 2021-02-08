#version 410 core

out vec4 FragColor;

in vec3 v_FragmentPosition;
in vec2 v_TexCoords;
in vec3 v_Normals;
in float v_Visibility;

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

uniform sampler2D u_Texture0;

struct Material {
    vec3 Diffuse;
    vec3 Specular;
    float Shine;
    float Dissolve;
};

uniform Material u_Material;

void main()
{
    vec4 Lighting = vec4(u_Material.Diffuse, 1.0f);

    vec3 nnormal = normalize(v_Normals);
    vec3 lightDirection = normalize(general.SunPosition - v_FragmentPosition);
    float intensity = dot(lightDirection, nnormal);

    if (intensity > 0.95) {
        // Do nothing!
    } else if (intensity > 0.5) {
        Lighting = vec4(u_Material.Diffuse * 0.5f, 1.0);
    }  else if (intensity > 0.25) {
        Lighting = vec4(u_Material.Diffuse * 0.25f, 1.0);
    } else {
        Lighting = vec4(u_Material.Diffuse * 0.125f, 1.0);
    }

    FragColor = texture(u_Texture0, v_TexCoords) * Lighting;
    FragColor = mix(vec4(general.SkyColor, 1.0), FragColor, v_Visibility);
}