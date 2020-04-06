#version 410 core

out vec4 FragColor;

in vec4 v_Color;
in vec2 v_TexCoords;

uniform sampler2D u_Texture0;

void main()
{
//   FragColor = texture(u_Texture0, v_TexCoords);
   FragColor = texture(u_Texture0, v_TexCoords) * v_Color;
}