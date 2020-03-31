
#include "System/Window.h"
#include "OpenGL/Shader.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"

const char *vsSource = "#version 410 core\n"
					   "layout (location = 0) in vec3 aPos;\n"
					   "void main()\n"
					   "{\n"
					   "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
					   "}\0";
const char *fsSource = "#version 410 core\n"
					   "out vec4 FragColor;\n"
					   "void main()\n"
					   "{\n"
					   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
					   "}\n\0";

int main(int argc, char const *argv[]) {

  Window window;
  Shader shader(vsSource, fsSource);
  VertexArray VAO;

  float vertices[] = {
	  -0.5f, -0.5f, 0.0f, // left
	  0.5f, -0.5f, 0.0f, // right
	  0.0f, 0.5f, 0.0f  // top
  };

  VAO.Bind();
  VertexBuffer VBO(9, vertices);
  VAO.SetLayout();

  while (window.WindowActive()) {
	window.Begin();
	shader.Bind();
	VAO.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	window.End();
  }

  return 0;
}

