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

// TODO: Uniform Block Cache

class Shader {

 private:
  uint32_t mID{0};
  std::map<const char *, int> mUniformLocations;
  std::vector<int> mStages;

 public:
  Shader();
  bool Create();
  virtual ~Shader();
  void Bind();

  inline uint32_t ID() { return mID; }

  void AddStage(GLenum pType, std::string pPath);

  void Bool(const char *pName, bool pValue);
  void Int(const char *pName, int pValue);
  void Float(const char *pName, float pValue);
  void Double(const char *pName, double pValue);
  void Vec2(const char *pName, const glm::vec2 &pValue);
  void Vec2(const char *pName, float x, float y);
  void Vec3(const char *pName, const glm::vec3 &pValue);
  void Vec3(const char *pName, float x, float y, float z);
  void Vec4(const char *pName, const glm::vec4 &pValue);
  void Vec4s(const char *pName, int size, const glm::vec4 pValue[]);
  void Vec4(const char *pName, float x, float y, float z, float w);
  void Mat2(const char *pName, const glm::mat2 &mat);
  void Mat3(const char *pName, const glm::mat3 &mat);
  void Mat4(const char *pName, const glm::mat4 &mat);

 private:
  virtual bool CompileShader(const char *pPath, int &pID);
  int UniformLocation(const char *pName);
  void RemoveStoredStages();
  const char *TypeString(uint32_t pType);
  void LogFullProgramInfo();
};
