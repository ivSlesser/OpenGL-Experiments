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

#include "../Graphics/Vertex.h"

VertexArray::VertexArray() {
  glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &id);
}

void VertexArray::SetLayout() {
  size_t sf = sizeof(float);
  int count = 0;
  int i = 0;

  // Position
  glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(count * sf));
  glEnableVertexAttribArray(i++);
  count += 3;

  // Color
  glVertexAttribPointer(i, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(count * sf));
  glEnableVertexAttribArray(i++);
  count += 4;

  // Texture Coordinates
  glVertexAttribPointer(i, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(count * sf));
  glEnableVertexAttribArray(i++);
  count += 2;

  // Normals
  glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(count * sf));
  glEnableVertexAttribArray(i++);
  count += 3;
}

void VertexArray::Bind() {
  glBindVertexArray(id);
}

