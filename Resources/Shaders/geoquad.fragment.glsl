#version 410 core

out vec4 FragColor;

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
   FragColor = vec4(u_Material.Diffuse, 1.0);
}