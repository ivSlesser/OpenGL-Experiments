#version 410 core

out vec4 FragColor;

in vec3 v_FragmentPosition;
in vec4 v_Color;
in vec2 v_TexCoords;
in vec3 v_Normals;
in float v_MatIndex;

uniform vec3 u_LightPosition;
uniform vec3 u_LightColor;
uniform vec3 u_CameraPosition;
uniform sampler2D u_Texture0;

const float AmbientStrength = 0.4;

struct Material {
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    float Shine;
    float Dissolve;
};

uniform Material u_Materials[100];

void main()
{
    Material mat = u_Materials[int(v_MatIndex)];

    // AMBIENT
    vec3 Ambient = AmbientStrength * u_LightColor * mat.Ambient;

    // DIFFUSE
    vec3 nnormal = normalize(v_Normals);
    vec3 lightDirection = normalize(u_LightPosition - v_FragmentPosition);
    float diff = max(dot(nnormal, lightDirection), 0.0);
    vec3 Diffuse = diff * u_LightColor * mat.Diffuse;

    // Specular
    vec3 viewDirection = normalize(u_CameraPosition - v_FragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, nnormal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), mat.Shine);
    vec3 Specular = spec * u_LightColor * mat.Specular;

    vec4 FinalColor = vec4(Ambient + Diffuse + Specular, 1.0);
    //mat.Dissolve);

    FragColor = texture(u_Texture0, v_TexCoords) * FinalColor;
}