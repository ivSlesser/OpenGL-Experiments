#version 410 core

out vec4 FragColor;

in vec3 v_FragmentPosition;
in vec4 v_ClipSpace;
in vec4 v_Color;
in vec2 v_TexCoords;
in vec3 v_Normals;


uniform vec3 u_LightPosition;
uniform vec3 u_LightColor;
uniform vec3 u_CameraPosition;

uniform sampler2D u_ReflectionTexture;
uniform sampler2D u_RefractionTexture;

const float AmbientStrength = 0.2;
const float SpecularStrength = 0.5;

void main()
{
    vec2 NDC = (v_ClipSpace.xy / v_ClipSpace.w) / 2.0 + 0.5;

    vec2 TexCoord_Reflection = vec2(NDC.x, -NDC.y);
    vec2 TexCoord_Refraction = vec2(NDC.x, NDC.y);

    vec4 reflection = texture(u_ReflectionTexture, TexCoord_Reflection);
    vec4 refraction = texture(u_RefractionTexture, TexCoord_Refraction);

    // AMBIENT
    vec3 Ambient = AmbientStrength * u_LightColor;

    // DIFFUSE
    vec3 nnormal = normalize(v_Normals);
    vec3 lightDirection = normalize(u_LightPosition - v_FragmentPosition);
    float diff = max(dot(nnormal, lightDirection), 0.0);
    vec3 Diffuse = diff * u_LightColor;

    // Specular
    vec3 viewDirection = normalize(u_CameraPosition - v_FragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, nnormal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
    vec3 Specular = SpecularStrength * spec * u_LightColor;

    vec4 Lighting = vec4(Ambient + Diffuse + Specular, 1.0f);

//    FragColor = texture(u_ReflectionTexture, v_TexCoords) * Lighting;
    FragColor = mix(reflection, refraction, 0.5);

}