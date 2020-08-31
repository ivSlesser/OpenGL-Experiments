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


#include "Shapes2D.h"


// Triangle ------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

std::vector<Vertex> Triangle::Vertices() {
  return {
      {{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},        // Left
      {{1.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},        // Right
      {{0.0f, 1.0f, 0.0f}, {0.5f, 1.0f}}         // Top
  };
}

std::vector<uint32_t> Triangle::Indices(uint32_t pOffset) {
  return {
      0 + pOffset, 1 + pOffset, 2 + pOffset
  };
}

// Rectangle -----------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

std::vector<Vertex> Rectangle::Vertices() {
  return {
      {{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},   // TR
      {{1.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},   // BR
      {{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},   // BL
      {{-1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},   // TL
  };
}

std::vector<uint32_t> Rectangle::Indices(uint32_t pOffset) {
  return {
      0 + pOffset, 1 + pOffset, 3 + pOffset,   // First triangle
      1 + pOffset, 2 + pOffset, 3 + pOffset    // Second triangle
  };
}

// Polygon -------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

void Polygon::Create(float pSides) {

  if (pSides < 3) {
    throw std::invalid_argument("Number of sides must be 3 or greater.");
  }

  // Central vertex
  mVertices.push_back(
      {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}
  );

  float halfPI = M_PI * 0.5f;
  float angleStep = (2 * M_PI) / pSides;

  for (int i = 0; i < pSides; ++i) {
    mIndices.push_back(0); // Centre.

    float x1 = 1.0f * cos(i * angleStep + halfPI);
    float y1 = 1.0f * sin(i * angleStep + halfPI);

    mIndices.push_back(mVertices.size());

    mVertices.push_back(
        {{x1, y1, 0.0f}, {1.0f, 1.0f}}
    );

    float x2 = 1.0f * cos((i + 1) * angleStep + halfPI);
    float y2 = 1.0f * sin((i + 1) * angleStep + halfPI);

    mIndices.push_back(mVertices.size());

    mVertices.push_back(
        {{x2, y2, 0.0f}, {1.0f, 1.0f}}
    );
  }
}
