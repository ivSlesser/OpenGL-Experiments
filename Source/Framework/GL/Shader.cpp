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
#include "Framework/Renderer.h"

// TODO: Doc
Shader::Shader() {
  id = glCreateProgram();
}

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

  for (int stage : m_Stages) {
    CHECK_GL_ERROR(glAttachShader(id, stage));
  }

  CHECK_GL_ERROR(glLinkProgram(id));

  int success = 0;
  char *infolog;
  CHECK_GL_ERROR(glGetProgramiv(id, GL_LINK_STATUS, &success));

  if (!success) {
    CHECK_GL_ERROR(glGetProgramInfoLog(id, 512, NULL, infolog));
    std::cout << infolog << std::endl;
    return false;
  }

  LogFullProgramInfo();

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
}

// TODO: Doc
void Shader::Bind() {
  CHECK_GL_ERROR(glUseProgram(id));
}

// TODO: Doc
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
  CHECK_GL_ERROR(glShaderSource(id, 1, &contentsPtr, nullptr));
  CHECK_GL_ERROR(glCompileShader(id));
  int success = 0;
  CHECK_GL_ERROR(glGetShaderiv(id, GL_COMPILE_STATUS, &success));

  if (!success) {
    GLint length = 0;
    CHECK_GL_ERROR(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
    char *message = (char *) alloca(length * sizeof(char));
    CHECK_GL_ERROR(glGetShaderInfoLog(id, length, &length, message));
    std::cout << message << std::endl;
    CHECK_GL_ERROR(glDeleteShader(id));
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
  CHECK_GL_ERROR(glUniform1i(UniformLocation(name), (int) value));
}

void Shader::Int(const char *name, int value) {
  CHECK_GL_ERROR(glUniform1i(UniformLocation(name), value));
}

void Shader::Float(const char *name, float value) {
  CHECK_GL_ERROR(glUniform1f(UniformLocation(name), value));
}

void Shader::Double(const char *name, double value) {
  CHECK_GL_ERROR(glUniform1d(UniformLocation(name), value));
}

void Shader::Vec2(const char *name, const glm::vec2 &value) {
  CHECK_GL_ERROR(glUniform2fv(UniformLocation(name), 1, &value[0]));
}

void Shader::Vec2(const char *name, float x, float y) {
  CHECK_GL_ERROR(glUniform2f(UniformLocation(name), x, y));
}

void Shader::Vec3(const char *name, const glm::vec3 &value) {
  CHECK_GL_ERROR(glUniform3fv(UniformLocation(name), 1, &value[0]));
}

void Shader::Vec3(const char *name, float x, float y, float z) {
  CHECK_GL_ERROR(glUniform3f(UniformLocation(name), x, y, z));
}

void Shader::Vec4(const char *name, const glm::vec4 &value) {
  CHECK_GL_ERROR(glUniform4fv(UniformLocation(name), 1, &value[0]));
}

void Shader::Vec4s(const char *name, int size, const glm::vec4 value[]) {
  CHECK_GL_ERROR(glUniform4fv(UniformLocation(name), size, glm::value_ptr(value[0])));
}

void Shader::Vec4(const char *name, float x, float y, float z, float w) {
  CHECK_GL_ERROR(glUniform4f(UniformLocation(name), x, y, z, w));
}

void Shader::Mat2(const char *name, const glm::mat2 &mat) {
  CHECK_GL_ERROR(glUniformMatrix2fv(UniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}

void Shader::Mat3(const char *name, const glm::mat3 &mat) {
  CHECK_GL_ERROR(glUniformMatrix3fv(UniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}

void Shader::Mat4(const char *name, const glm::mat4 &mat) {
  CHECK_GL_ERROR(glUniformMatrix4fv(UniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}

/**
 * Removes the stored stages, deleting the shader via the API
 * and then clearing the list.
 */
void Shader::RemoveStoredStages() {
  for (int stage : m_Stages) {
    CHECK_GL_ERROR(glDeleteShader(stage));
  }

  m_Stages.clear();
}

// TODO: Doc
const char *Shader::TypeString(uint32_t type) {
  // https://www.khronos.org/opengl/wiki/OpenGL_Type
  switch (type) {
    case GL_BOOL: return "Bool";
    case GL_INT: return "Int";
    case GL_FLOAT: return "float";
    case GL_FLOAT_VEC2: return "Vec2";
    case GL_FLOAT_VEC3: return "Vec3";
    case GL_FLOAT_VEC4: return "Vec4";
    case GL_FLOAT_MAT2: return "mat2";
    case GL_FLOAT_MAT3: return "mat3";
    case GL_FLOAT_MAT4: return "mat4";
    case GL_SAMPLER_2D: return "Sampler2D";
    case GL_SAMPLER_3D: return "Sampler3D";
    case GL_SAMPLER_CUBE: return "SamplerCube";
    case GL_SAMPLER_2D_SHADOW: return "Sampler2DShadow";
    default: break;
  }
  return "other";
}

// TODO: Doc
void Shader::LogFullProgramInfo() {

  std::cout << "\n";

  std::cout << "ShaderProgram id " << id << " log:" << std::endl;

  int params = -1;
  glGetProgramiv(id, GL_LINK_STATUS, &params);
  std::cout << "GL_LINK_STATUS = " << params << std::endl;

  glGetProgramiv(id, GL_ATTACHED_SHADERS, &params);
  std::cout << "GL_ATTACHED_SHADERS = " << params << std::endl;;

  glGetProgramiv(id, GL_ACTIVE_ATTRIBUTES, &params);
  std::cout << "GL_ACTIVE_ATTRIBUTES = " << params << std::endl;

  const char *output_format = "\t%d -> Type: %-20s Name: %-20s Location: %-20d";

  for (int i = 0; i < params; i++) {
    char name[64];
    int max_length = 64;
    int actual_length = 0;
    int size = 0;
    GLenum type;
    glGetActiveAttrib(id, i, max_length, &actual_length, &size, &type, name);

    if (size > 1) {
      for (int j = 0; j < size; j++) {
        char long_name[64];
        std::cout << name << "[" << j << "]" << std::endl;
        int location = glGetAttribLocation(id, long_name);
        std::cout << "\t" << i << " -> Type: " << TypeString(type) << ", Name: " << name << ", Location: " << location << std::endl;
      }
    } else {
      int location = glGetAttribLocation(id, name);
      std::cout << "\t" << i << " -> Type: " << TypeString(type) << ", Name: " << name << ", Location: " << location << std::endl;
    }
  }

  glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &params);
  for (int i = 0; i < params; i++) {
    char name[64];
    int max_length = 64;
    int actual_length = 0;
    int size = 0;
    GLenum type;
    glGetActiveUniform(id, i, max_length, &actual_length, &size, &type, name);
    if (size > 1) {
      for (int j = 0; j < size; j++) {
        char long_name[64];
        std::cout << name << "[" << j << "]" << std::endl;
        int location = glGetUniformLocation(id, long_name);
        std::cout << "\t" << i << " -> Type: " << TypeString(type) << ", Name: " << long_name << ", Location: " << location << std::endl;
      }
    } else {
      int location = glGetUniformLocation(id, name);
      std::cout << "\t" << i << " -> Type: " << TypeString(type) << ", Name: " << name << ", Location: " << location << std::endl;
    }
  }

  int ML = 2048;
  int AL = 0;
  char IL[2048];
  glGetProgramInfoLog(id, ML, &AL, IL);
  std::cout << "Program info log " << id << std::endl;
  std::cout << IL << std::endl;
  std::cout << "\n";
}


