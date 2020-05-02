#version 410 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in vec4 v_Color[];

out vec4 g_Color;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;


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
    gl_Position = u_ViewProjection * u_Model * (gl_in[0].gl_Position + offset);
    g_Color = v_Color[0];
    EmitVertex();
}

void CreateBillboard(vec4 offset) {
    gl_Position = u_ViewProjection * u_Model * gl_in[0].gl_Position + offset;
    g_Color = v_Color[0];
    EmitVertex();
}