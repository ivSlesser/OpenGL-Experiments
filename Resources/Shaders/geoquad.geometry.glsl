#version 410 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

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

uniform mat4 u_Model;

void CreateVertex(vec4);
void CreateBillboard(vec4);

void main() {

    CreateVertex(vec4(-1.0f, -1.0f, 0.0, 0.0)); // Bottom left
    CreateVertex(vec4( 1.0f, -1.0f, 0.0, 0.0)); // Bottom right
    CreateVertex(vec4(-1.0f,  1.0f, 0.0, 0.0)); // Top right
    CreateVertex(vec4( 1.0f,  1.0f, 0.0, 0.0)); // Top right

//    CreateBillboard(vec4(-1.0f, -1.0f, 0.0, 0.0)); // Bottom left
//    CreateBillboard(vec4( 1.0f, -1.0f, 0.0, 0.0)); // Bottom right
//    CreateBillboard(vec4(-1.0f,  1.0f, 0.0, 0.0)); // Top right
//    CreateBillboard(vec4( 1.0f,  1.0f, 0.0, 0.0)); // Top right

    EndPrimitive();

}

void CreateVertex(vec4 offset) {
    gl_Position = camera.ViewProjection * u_Model * (gl_in[0].gl_Position + offset);
    EmitVertex();
}

void CreateBillboard(vec4 offset) {
    gl_Position = camera.ViewProjection * u_Model * gl_in[0].gl_Position + offset;
    EmitVertex();
}