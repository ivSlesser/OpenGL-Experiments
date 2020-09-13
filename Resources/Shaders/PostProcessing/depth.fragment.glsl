#version 410 core

out vec4 FragColor;

in vec2 v_TexCoords;

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

// PP On/Off Toggles
uniform bool u_Greyscale;
uniform bool u_Invert;

// PP Related Variables
uniform float u_ContrastStrength;
uniform float u_BlurTargetWidth;

void main()
{
    vec4 FinalColour = texture(u_Texture0, v_TexCoords);

    // Greyscale -------------------------------------------------------------------------------------------------------
    if (u_Greyscale) {
        float GREY = 0.2126 * FinalColour.r + 0.7152 * FinalColour.g + 0.0722 * FinalColour.b;
        FinalColour = vec4(GREY, GREY, GREY, 1.0);
    }

    // Invert ----------------------------------------------------------------------------------------------------------
    if (u_Invert) {
        FinalColour = vec4(vec3(1.0 - FinalColour), 1.0);
    }

    // Contrast --------------------------------------------------------------------------------------------------------
    FinalColour.rgb =  (FinalColour.rgb - 0.5) * (1.0 + u_ContrastStrength) + 0.5;

    // Output ----------------------------------------------------------------------------------------------------------
    FragColor = FinalColour;
}