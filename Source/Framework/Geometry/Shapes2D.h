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
#include "./Vertex.h"

// Triangle ------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

struct Triangle {
  static std::vector<Vertex> Vertices();
  static std::vector<uint32_t> Indices(uint32_t pOffset = 0);
  inline static uint32_t VertexCount() { return 3; };
  inline static uint32_t IndexCount() { return 3; };
};

// Rectangle -----------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

struct Rectangle {
  static std::vector<Vertex> Vertices();
  static std::vector<uint32_t> Indices(uint32_t pOffset = 0);
  inline static uint32_t VertexCount() { return 4; };
  inline static uint32_t IndexCount() { return 6; };
};

// Polygon -------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

struct Polygon {
  std::vector<Vertex> mVertices;
  std::vector<unsigned> mIndices;
  void Create(float pSides = 5);
  inline std::vector<Vertex> &Vertices() { return mVertices; }
  inline std::vector<unsigned> &Indices() { return mIndices; };
  inline const int VertexCount() const { return mVertices.size(); };
  inline const int IndexCount() const { return mIndices.size(); }
};