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
    // AMBIENT
    vec3 Ambient = general.AmbientStrength * general.SunColor * u_Material.Diffuse;

    // DIFFUSE
    vec3 nnormal = normalize(v_Normals);
    vec3 lightDirection = normalize(general.SunPosition - v_FragmentPosition);
    float diff = max(dot(nnormal, lightDirection), 0.0);
    vec3 Diffuse = diff * general.SunColor * u_Material.Diffuse;

    // SPECULAR
    vec3 viewDirection = normalize(camera.Position - v_FragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, nnormal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), u_Material.Shine);
    vec3 Specular = general.SpecularStrength * spec * general.SunColor * u_Material.Specular;

    // FINAL LIGHTING CALCULATION
    vec4 Lighting = vec4(Ambient + Diffuse + Specular, 1.0f);

    FragColor = texture(u_Texture0, v_TexCoords) * Lighting;
    FragColor = mix(vec4(general.SkyColor, 1.0), FragColor, v_Visibility);
}