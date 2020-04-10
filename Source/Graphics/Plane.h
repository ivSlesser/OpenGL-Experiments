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
#include "Vertex.h"

class Plane {

 private:
  std::vector<Vertex> vertices;
  std::vector<unsigned> indices;

 public:
  Plane(glm::vec4 color = glm::vec4(1.0f),
		const glm::vec3 &pos = glm::vec3(0.0f),
		const glm::vec2 &size = glm::vec2(10.0f),
		float resolution = 5);

  inline std::vector<Vertex> &Vertices() { return vertices; }
  inline std::vector<unsigned> &Indices() { return indices; };
  inline const int VertexCount() const { return vertices.size(); };
  inline const int IndexCount() const { return indices.size(); }

};
