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
#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"
#include "Properties/Material.h"

class Mesh {

 public:
  VertexArray VAO;
  VertexBuffer VBO;
  IndexBuffer IBO;
  unsigned int VertexCount = 0;
  unsigned int IndexCount = 0;
  std::string Name = "Mesh";
  Material iMaterial;
  bool UsesMaterials = false;

  bool Load(const std::vector<Vertex> &pVertices, const std::vector<unsigned int> &pIndices, const Material &pMaterial = {});
  bool LoadInstanced(const std::vector<Vertex> &pVertices, const std::vector<unsigned int> &pIndices, const std::vector<glm::mat4> &pMatrices, const Material &pMaterial = {});
  inline void Bind() { VAO.Bind(); IBO.Bind(); }
};
