#version 410 core

out vec4 FragColor;

in vec3 v_FragmentPosition;
in vec4 v_Color;
in vec2 v_TexCoords;
in vec3 v_Normals;
in float v_Visibility;

uniform vec3 u_LightPosition;
uniform vec3 u_CameraPosition;
uniform sampler2D u_Texture0;
uniform vec4 u_SkyColor;

const float AmbientStrength = 0.2; // TODO: Move to Renderer
const float SpecularStrength = 0.5; // TODO: Move to Renderer

void main()
{
    vec3 LightColor = vec3(0.9, 0.9, 0.9);

    // AMBIENT
    vec3 Ambient = AmbientStrength * LightColor;

    // DIFFUSE
    vec3 nnormal = normalize(v_Normals);
    vec3 lightDirection = normalize(u_LightPosition - v_FragmentPosition);
    float diff = max(dot(nnormal, lightDirection), 0.0);
    vec3 Diffuse = diff * LightColor;

    // Specular
    vec3 viewDirection = normalize(u_CameraPosition - v_FragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, nnormal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
    vec3 Specular = SpecularStrength * spec * LightColor;

    vec4 Lighting = vec4(Ambient + Diffuse + Specular, 1.0f);

    FragColor = texture(u_Texture0, v_TexCoords) * Lighting * v_Color;
    FragColor = mix(u_SkyColor, FragColor, v_Visibility);
}