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


#include "VertexBuffer.h"
#include "Framework/Renderer.h"

VertexBuffer::VertexBuffer() {
  CHECK_GL_ERROR(glGenBuffers(1, &id));
}

void VertexBuffer::Init(const std::vector<Vertex> &data) {
  CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, id));
  CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), data.data(), GL_STATIC_DRAW));
}

void VertexBuffer::Bind() {
  CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, id));
}

void VertexBuffer::Create(const std::vector<Vertex2> &data) {
  CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, id));
  CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex2), data.data(), GL_STATIC_DRAW));
}

void VertexBuffer::Destroy() {
  CHECK_GL_ERROR(glDeleteBuffers(1, &id));
}
