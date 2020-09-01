#version 410 core

out vec4 FragColor;

in vec3 v_FragmentPosition;
in vec2 v_TexCoords;
in vec3 v_Normals;
in float v_Visibility;

uniform vec3 u_LightPosition;
uniform vec3 u_LightColor;
uniform vec3 u_CameraPosition;
uniform vec4 u_SkyColor;

uniform sampler2D u_Texture0;

const float AmbientStrength = 0.2;
const float SpecularStrength = 0.5;

struct Material {
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    float Shine;
    float Dissolve;
};

uniform Material u_Material;

void main()
{
    // AMBIENT
    vec3 Ambient = AmbientStrength * u_LightColor * u_Material.Ambient;

    // DIFFUSE
    vec3 nnormal = normalize(v_Normals);
    vec3 lightDirection = normalize(u_LightPosition - v_FragmentPosition);
    float diff = max(dot(nnormal, lightDirection), 0.0);
    vec3 Diffuse = diff * u_LightColor * u_Material.Diffuse;

    // SPECULAR
    vec3 viewDirection = normalize(u_CameraPosition - v_FragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, nnormal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), u_Material.Shine);
    vec3 Specular = SpecularStrength * spec * u_LightColor * u_Material.Specular;

    // FINAL LIGHTING CALCULATION
    vec4 Lighting = vec4(Ambient + Diffuse + Specular, 1.0f);

    FragColor = texture(u_Texture0, v_TexCoords) * Lighting;
    FragColor = mix(u_SkyColor, FragColor, v_Visibility);
}