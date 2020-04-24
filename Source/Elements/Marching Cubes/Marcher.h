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
#include "Graphics/Vertex.h"
#include "Math/Random/Perlin.h"

class Marcher {
 private:
  Perlin m_Perlin;

  std::vector<float> m_Data;
  glm::vec2 m_Dimensions;

  std::vector<Vertex> m_Vertices;
  std::vector<unsigned> m_Indices;

  float m_Threshold;

 public:
  Marcher(const glm::vec2 &pDimensions);

  void March(float pThreshold = 0.1f);

  inline std::vector<Vertex> Vertices() { return m_Vertices; }
  inline std::vector<unsigned> Indices() { return m_Indices; }
  inline int VertexCount() { return m_Vertices.size(); }
  inline int IndexCount() { return m_Indices.size(); }

 private:
  void CellOperation(float pCube[], const glm::vec3 &pPosition);
  int GetCubeConfiguration(float cube[]);

  // Indexes
  inline int I2D(int x, int z) { return x + z * m_Dimensions.x + 1; };
  inline int I3D(int x, int y, int z) { return (z * (m_Dimensions.x + 1) * (m_Dimensions.y + 1)) + (y * (m_Dimensions.x + 1)) + x;}

};
