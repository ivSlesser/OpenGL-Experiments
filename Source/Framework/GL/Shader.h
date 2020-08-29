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


#pragma once

#include "Common.h"

class Shader {

 private:
  int id{0};
  std::map<const char *, int> uniform_locations;
  std::vector<int> m_Stages;

 public:
  Shader();
  bool Compile();
  virtual ~Shader();
  void Bind();

  void AddStage(GLenum p_Type, std::string p_Path);

  void Bool(const char *name, bool value);
  void Int(const char *name, int value);
  void Float(const char *name, float value);
  void Double(const char *name, double value);
  void Vec2(const char *name, const glm::vec2 &value);
  void Vec2(const char *name, float x, float y);
  void Vec3(const char *name, const glm::vec3 &value);
  void Vec3(const char *name, float x, float y, float z);
  void Vec4(const char *name, const glm::vec4 &value);
  void Vec4s(const char *name, int size, const glm::vec4 value[]);
  void Vec4(const char *name, float x, float y, float z, float w);
  void Mat2(const char *name, const glm::mat2 &mat);
  void Mat3(const char *name, const glm::mat3 &mat);
  void Mat4(const char *name, const glm::mat4 &mat);

 private:
  virtual bool CompileShader(const char *filePath, int &id);
  int UniformLocation(const char *name);
  void RemoveStoredStages();
  const char *TypeString(uint32_t type);
  void LogFullProgramInfo();
};
