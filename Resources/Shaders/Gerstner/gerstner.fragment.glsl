#version 410 core

out vec4 FragColor;

in vec3 v_FragmentPosition;
in vec4 v_Color;
in vec2 v_TexCoords;
in vec3 v_Normals;

uniform vec3 u_LightPosition;
uniform vec3 u_CameraPosition;
uniform sampler2D u_Texture0;

const float AmbientStrength = 0.2;
const float SpecularStrength = 0.5;

void main()
{
    //FragColor = texture(u_Texture0, v_TexCoords) * v_Color;

    // AMBIENT
    vec3 Ambient = AmbientStrength * vec3(1.0f, 1.0f, 1.0f);

    // DIFFUSE
    vec3 nnormal = normalize(v_Normals);
    vec3 lightDirection = normalize(u_LightPosition - v_FragmentPosition);
    float diff = max(dot(nnormal, lightDirection), 0.0);
    vec3 Diffuse = diff * vec3(1.0f, 1.0f, 1.0f);

    // Specular
    vec3 viewDirection = normalize(u_CameraPosition - v_FragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, nnormal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
    vec3 Specular = SpecularStrength * spec * vec3(1.0f, 1.0f, 1.0f);

    vec4 Lighting = vec4(Ambient + Diffuse + Specular, 1.0f);

    FragColor = texture(u_Texture0, v_TexCoords) * Lighting * v_Color;

}