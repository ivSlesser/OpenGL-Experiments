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


#include "Shapes3D.h"

// Cube ------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

std::vector<Vertex2> Cube::Vertices() {
  return {
    {{-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}, {-0.5f, -0.5f, -0.5f}},
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, { 0.5f, -0.5f, -0.5f}},
    {{1.0f, 1.0f, -1.0f}, {0.0f, 1.0f}, { 0.5f,  0.5f, -0.5f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f}, {-0.5f,  0.5f, -0.5f}},

    {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f}, {-0.5f, -0.5f,  0.5f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f}, { 0.5f, -0.5f,  0.5f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, { 0.5f,  0.5f,  0.5f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {-0.5f,  0.5f,  0.5f}}
  };
}

std::vector<uint32_t> Cube::Indices(uint32_t pOffset) {
  return {
      0 + pOffset, 1 + pOffset, 3 + pOffset, 3 + pOffset, 1 + pOffset, 2 + pOffset,
      1 + pOffset, 5 + pOffset, 2 + pOffset, 2 + pOffset, 5 + pOffset, 6 + pOffset,
      5 + pOffset, 4 + pOffset, 6 + pOffset, 6 + pOffset, 4 + pOffset, 7 + pOffset,
      4 + pOffset, 0 + pOffset, 7 + pOffset, 7 + pOffset, 0 + pOffset, 3 + pOffset,
      3 + pOffset, 2 + pOffset, 7 + pOffset, 7 + pOffset, 2 + pOffset, 6 + pOffset,
      4 + pOffset, 5 + pOffset, 0 + pOffset, 0 + pOffset, 5 + pOffset, 1 + pOffset
  };
}