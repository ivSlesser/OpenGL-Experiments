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


#include "VertexArray.h"

#include "Framework/Geometry/Vertex.h"
#include "Framework/Renderer.h"

VertexArray::VertexArray() {
  CHECK_GL_ERROR(glGenVertexArrays(1, &m_ID));
  CHECK_GL_ERROR(glBindVertexArray(m_ID));
}

void VertexArray::SetLayout() {
  size_t sf = sizeof(float);

  // Position
  CHECK_GL_ERROR(glVertexAttribPointer(m_AttribIDMax, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(m_AttribCount * sf)));
  CHECK_GL_ERROR(glEnableVertexAttribArray(m_AttribIDMax++));
  m_AttribCount += 3;

  // Texture Coordinates
  CHECK_GL_ERROR(glVertexAttribPointer(m_AttribIDMax, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(m_AttribCount * sf)));
  CHECK_GL_ERROR(glEnableVertexAttribArray(m_AttribIDMax++));
  m_AttribCount += 2;

  // Normals
  CHECK_GL_ERROR(glVertexAttribPointer(m_AttribIDMax, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(m_AttribCount * sf)));
  CHECK_GL_ERROR(glEnableVertexAttribArray(m_AttribIDMax++));
  m_AttribCount += 3;
}

void VertexArray::Bind() {
  CHECK_GL_ERROR(glBindVertexArray(m_ID));
}

void VertexArray::AttachInstancedMatrixBuffer(const std::vector<glm::mat4> &pMatrices) {

  Bind();

  glGenBuffers(1, &m_IBufferID);
  glBindBuffer(GL_ARRAY_BUFFER, m_IBufferID);
  glBufferData(GL_ARRAY_BUFFER, pMatrices.size() * sizeof(glm::mat4), pMatrices.data(), GL_STATIC_DRAW);

  auto s = sizeof(glm::vec4);

  glVertexAttribPointer(m_AttribIDMax, 4, GL_FLOAT, GL_FALSE, 4 * s, (void*)(0 * s));
  glEnableVertexAttribArray(m_AttribIDMax);
  glVertexAttribDivisor(m_AttribIDMax++, 1);
  m_AttribCount += 4;

  glVertexAttribPointer(m_AttribIDMax, 4, GL_FLOAT, GL_FALSE, 4 * s, (void*)(1 * s));
  glEnableVertexAttribArray(m_AttribIDMax);
  glVertexAttribDivisor(m_AttribIDMax++, 1);
  m_AttribCount += 4;

  glVertexAttribPointer(m_AttribIDMax, 4, GL_FLOAT, GL_FALSE, 4 * s, (void*)(2 * s));
  glEnableVertexAttribArray(m_AttribIDMax);
  glVertexAttribDivisor(m_AttribIDMax++, 1);
  m_AttribCount += 4;

  glVertexAttribPointer(m_AttribIDMax, 4, GL_FLOAT, GL_FALSE, 4 * s, (void*)(3 * s));
  glEnableVertexAttribArray(m_AttribIDMax);
  glVertexAttribDivisor(m_AttribIDMax++, 1);
  m_AttribCount += 4;
}

void VertexArray::Destroy() {
  CHECK_GL_ERROR(glDeleteVertexArrays(1, &m_ID));
}

