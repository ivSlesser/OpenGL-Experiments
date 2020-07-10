// MIT License
//
// Copyright (c) 2020 Ian Vincent Slesser
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#include "Shader.h"
#include "Renderer.h"

/**
 * Compiles generated shaders into a program, there must be at least 2 shader stages added before
 * compilation will occur.
 *
 * @return True if compilation was successful.
 */
bool Shader::Compile() {

  // At a minimum we need a vertex & fragment stage, broadly we're checking size < 3 here,
  // but future work could check to see the stage type added.
  if (m_Stages.size() < 2) {
    std::cout << "Shader::Init - Error: At a minimum requires Vertex & Fragment stage to be added" << std::endl;
    return false;
  }

  id = glCreateProgram();

  for(int stage : m_Stages) {
    glAttachShader(id, stage);
  }

  glLinkProgram(id);

  int success = 0;
  char *infolog;
  glGetProgramiv(id, GL_LINK_STATUS, &success);

  if (!success) {
	glGetProgramInfoLog(id, 512, NULL, infolog);
	std::cout << infolog << std::endl;
    return false;
  }


  RemoveStoredStages();

  printf("Program created with id: %d\n", id);

  return true;
}

/**
 * Adds a shader stage to the shader lists ready for program compilation,
 * checks that the type is supported and that a vertex shader is or has been added,
 * the generates and compiles the actual shader.
 *
 * @param p_Type Type of shader being added.
 * @param p_Path Path to shader file.
 */
void Shader::AddStage(GLenum p_Type, std::string p_Path) {
  // Check to ensure p_Type is supported.
  if (p_Type != GL_VERTEX_SHADER && p_Type != GL_FRAGMENT_SHADER && p_Type != GL_GEOMETRY_SHADER) {
    std::cout << "Shader::AddStage - Error: Stage unsupported" << std::endl;
    std::abort();
  }

  // Check to ensure we have a vertex shader at element 0.
  if (p_Type != GL_VERTEX_SHADER && m_Stages.size() == 0) {
    std::cout << "Shader::AddStage - Error: Vertex stage must be added first." << std::endl;
    std::abort();
  }

  // Generate and attempt to compile.
  int shaderID = glCreateShader(p_Type);
  if (!CompileShader(p_Path.c_str(), shaderID)) {
    std::abort();
  }

  // Add to our stages list.
  m_Stages.push_back(shaderID);
}

Shader::~Shader() {
  glDeleteProgram(id);
}

void Shader::Bind() {
  CHECK_GL_ERROR(glUseProgram(id));
}

bool Shader::CompileShader(const char *filePath, int &id) {
  std::ifstream shaderFile(filePath);

  if (shaderFile.fail()) {
	printf("[%s]%d: Could not load file %s (%s)", __FILE__, __LINE__, filePath, strerror(errno));
	return false;
  }

  std::string fileContents;
  std::string line;

  while (std::getline(shaderFile, line)) {
	fileContents += line + "\n";
  }

  shaderFile.close();
  const char *contentsPtr = fileContents.c_str();
  glShaderSource(id, 1, &contentsPtr, nullptr);
  glCompileShader(id);
  int success = 0;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);

  if (!success) {
	GLint length = 0;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
	char *message = (char *) alloca(length * sizeof(char));
	glGetShaderInfoLog(id, length, &length, message);
	std::cout << message << std::endl;
	glDeleteShader(id);
	return false;
  }

  return true;
}

int Shader::UniformLocation(const char *name) {
  if (uniform_locations.find(name) != uniform_locations.end()) {
	return uniform_locations[name];
  } else {
	int a = glGetUniformLocation(id, name);
	uniform_locations[name] = a;
	return a;
  }
}

void Shader::Bool(const char *name, bool value) {
  glUniform1i(UniformLocation(name), (int) value);
}

void Shader::Int(const char *name, int value) {
  glUniform1i(UniformLocation(name), value);
}

void Shader::Float(const char *name, float value) {
  glUniform1f(UniformLocation(name), value);
}

void Shader::Double(const char *name, double value) {
  glUniform1d(UniformLocation(name), value);
}

void Shader::Vec2(const char *name, const glm::vec2 &value) {
  glUniform2fv(UniformLocation(name), 1, &value[0]);
}

void Shader::Vec2(const char *name, float x, float y) {
  glUniform2f(UniformLocation(name), x, y);
}

void Shader::Vec3(const char *name, const glm::vec3 &value) {
  glUniform3fv(UniformLocation(name), 1, &value[0]);
}

void Shader::Vec3(const char *name, float x, float y, float z) {
  glUniform3f(UniformLocation(name), x, y, z);
}

void Shader::Vec4(const char *name, const glm::vec4 &value) {
  glUniform4fv(UniformLocation(name), 1, &value[0]);
}

void Shader::Vec4s(const char *name, int size, const glm::vec4 value[]) {
  glUniform4fv(UniformLocation(name), size, glm::value_ptr(value[0]));
}

void Shader::Vec4(const char *name, float x, float y, float z, float w) {
  glUniform4f(UniformLocation(name), x, y, z, w);
}

void Shader::Mat2(const char *name, const glm::mat2 &mat) {
  glUniformMatrix2fv(UniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::Mat3(const char *name, const glm::mat3 &mat) {
  glUniformMatrix3fv(UniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::Mat4(const char *name, const glm::mat4 &mat) {
  glUniformMatrix4fv(UniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

/**
 * Removes the stored stages, deleting the shader via the API
 * and then clearing the list.
 */
void Shader::RemoveStoredStages() {
  for(int stage : m_Stages) {
    glDeleteShader(stage);
  }

  m_Stages.clear();
}

