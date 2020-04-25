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


#include "Cube.h"

std::vector<Vertex> Cube::Vertices(glm::vec4 color) {
  return Cube::Vertices(0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, color);
}

std::vector<Vertex> Cube::Vertices(float x, float y, float z, float w, float h, float d, glm::vec4 color) {
  std::vector<Vertex> vertices(8);

  vertices[0] = {{x - w, y - h, z - d}, color, {1.0f, 0.0f}, {-0.5f, -0.5f, -0.5f}};
  vertices[1] = {{x + w, y - h, z - d}, color, {0.0f, 0.0f}, { 0.5f, -0.5f, -0.5f}};
  vertices[2] = {{x + w, y + h, z - d}, color, {0.0f, 1.0f}, { 0.5f,  0.5f, -0.5f}};
  vertices[3] = {{x - w, y + h, z - d}, color, {1.0f, 1.0f}, {-0.5f,  0.5f, -0.5f}};

  vertices[4] = {{x - w, y - h, z + d}, color, {0.0f, 0.0f}, {-0.5f, -0.5f,  0.5f}};
  vertices[5] = {{x + w, y - h, z + d}, color, {1.0f, 0.0f}, { 0.5f, -0.5f,  0.5f}};
  vertices[6] = {{x + w, y + h, z + d}, color, {1.0f, 1.0f}, { 0.5f,  0.5f,  0.5f}};
  vertices[7] = {{x - w, y + h, z + d}, color, {0.0f, 1.0f}, {-0.5f,  0.5f,  0.5f}};

  return vertices;
}

std::vector<unsigned> Cube::Indices() {
  std::vector<unsigned int> indices = {
	  0, 1, 3, 3, 1, 2,
	  1, 5, 2, 2, 5, 6,
	  5, 4, 6, 6, 4, 7,
	  4, 0, 7, 7, 0, 3,
	  3, 2, 7, 7, 2, 6,
	  4, 5, 0, 0, 5, 1};
  return indices;
}

int Cube::VertexCount() {
  return 8;
}

int Cube::IndexCount() {
  return 36;
}
