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
  std::vector<Vertex> vertices(36);

  // Front
  vertices[0] = {{x - w, y - h, z - d}, color, {1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}}; // BL
  vertices[1] = {{x + w, y - h, z - d}, color, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}}; // TL
  vertices[2] = {{x + w, y + h, z - d}, color, {0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}}; // TR
  vertices[3] = {{x + w, y + h, z - d}, color, {0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}}; // TR
  vertices[4] = {{x - w, y + h, z - d},color,  {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}}; // BR
  vertices[5] = {{x - w, y - h, z - d},color,  {1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}}; // BL

  // Back
  vertices[6] = {{x - w, y - h, z + d}, color, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}; // BL
  vertices[7] = {{x + w, y - h, z + d},color,  {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}; // BR
  vertices[8] = {{x + w, y + h, z + d}, color, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}; // TR
  vertices[9] = {{x + w, y + h, z + d},color,  {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}; // TR
  vertices[10] = {{x - w, y + h, z + d},color,  {0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}; // TL
  vertices[11] = {{x - w, y - h, z + d},color,  {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}; // BL

  // Right
  vertices[12] = {{x + -w, y + h, z + d},color,  {1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}}; // TR
  vertices[13] = {{x + -w, y + h, z + -d},color,  {0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}}; // TL
  vertices[14] = {{x + -w, y + -h, z + -d},color,  {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}}; // BL
  vertices[15] = {{x + -w, y + -h, z + -d},color,  {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}}; // BL
  vertices[16] = {{x + -w, y + -h, z + d},color,  {1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}}; // BR
  vertices[17] = {{x + -w, y + h, z + d},color,  {1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}}; // TR

  // Left
  vertices[18] = {{x + w, y + h, z + d},color,  {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}}; // TL
  vertices[19] = {{x + w, y + h, z + -d},color,  {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}}; // TR
  vertices[20] = {{x + w, y + -h, z + -d},color,  {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}}; // BR
  vertices[21] = {{x + w, y + -h, z + -d},color,  {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}}; // BR
  vertices[22] = {{x + w, y + -h, z + d},color,  {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}}; // BL
  vertices[23] = {{x + w, y + h, z + d},color,  {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}}; // TL

  // Bottom
//  vertices[24] = {{x + -w, y + -h, z + -d},color,  {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}; // TR
//  vertices[25] = {{x + w, y + -h, z + -d},color,  {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}; // BL
//  vertices[26] = {{x + w, y + -h, z + d},color,  {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}}; // BR
//  vertices[27] = {{x + w, y + -h, z + d},color,  {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}}; // BR
//  vertices[28] = {{x + -w, y + -h, z + d},color,  {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}}; // TR
//  vertices[29] = {{x + -w, y + -h, z + -d},color,  {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}; // TL

  vertices[24] = {{x + -w, y + -h, z + -d},color,  {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}}; // TR
  vertices[25] = {{x + w, y + -h, z + -d},color,  {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}; // BL
  vertices[26] = {{x + w, y + -h, z + d},color,  {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}; // BR
  vertices[27] = {{x + w, y + -h, z + d},color,  {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}; // BR
  vertices[28] = {{x + -w, y + -h, z + d},color,  {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}}; // TR
  vertices[29] = {{x + -w, y + -h, z + -d},color,  {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}}; // TL

  // Top
  vertices[30] = {{x + -w, y + h, z + -d}, color, {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}}; // BR
  vertices[31] = {{x + w, y + h, z + -d},color,  {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}}; // BL
  vertices[32] = {{x + w, y + h, z + d},color,  {1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}}; // TL
  vertices[33] = {{x + w, y + h, z + d},color,  {1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}}; // TL
  vertices[34] = {{x + -w, y + h, z + d}, color, {1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}}; // TR
  vertices[35] = {{x + -w, y + h, z + -d}, color,  {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}}; // BR

  return vertices;
}

std::vector<unsigned> Cube::Indices() {
  std::vector<unsigned int> indices = {};
  return indices;
}

int Cube::VertexCount() {
  return 36;
}

int Cube::IndexCount() {
  return 0;
}
