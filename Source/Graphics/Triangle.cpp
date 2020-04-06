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


#include "Triangle.h"

std::vector<Vertex> Triangle::Vertices(float x, float y, float w, float h) {
  std::vector<Vertex> vertices = {
	  {x - w, y - h, 0.0f},        // Left
	  {x + w, y - h, 0.0f},        // Right
	  {x, y + h, 0.0f}            	   // Top
  };
  return vertices;
}
std::vector<unsigned> Triangle::Indices() {
  std::vector<unsigned int> indices = {
	  0, 1, 2
  };

  return indices;
}

int Triangle::VertexCount() {
  return 3;
}

int Triangle::IndexCount() {
  return 3;
}
