#version 410 core

out vec4 FragColor;

in vec3 v_FragmentPosition;
in vec2 v_TexCoords;
in vec3 v_Normals;
in float v_Visibility;

layout (std140) uniform Matrices
{
    mat4 View;
    mat4 Projection;
    mat4 ViewProjection;
};

layout (std140) uniform Lighting
{
    vec3 SkyColor;
    float AmbientStrength;
    vec3 SunColor;
    float SpecularStrength;
    vec3 SunPosition;
};

uniform vec3 u_CameraPosition;
uniform float u_Time;
uniform float u_DeltaTime;

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
    vec3 Ambient = AmbientStrength * SunColor * u_Material.Diffuse;

    // DIFFUSE
    vec3 nnormal = normalize(v_Normals);
    vec3 lightDirection = normalize(SunPosition - v_FragmentPosition);
    float diff = max(dot(nnormal, lightDirection), 0.0);
    vec3 Diffuse = diff * SunColor * u_Material.Diffuse;

    // SPECULAR
    vec3 viewDirection = normalize(u_CameraPosition - v_FragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, nnormal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), u_Material.Shine);
    vec3 Specular = SpecularStrength * spec * SunColor * u_Material.Specular;

    // FINAL LIGHTING CALCULATION
    vec4 Lighting = vec4(Ambient + Diffuse + Specular, 1.0f);

    FragColor = texture(u_Texture0, v_TexCoords) * Lighting;
    FragColor = mix(vec4(SkyColor, 1.0), FragColor, v_Visibility);
}