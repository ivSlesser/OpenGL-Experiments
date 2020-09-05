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

/**
 * Construct the object, generating a buffer ID.
 */
VertexBuffer::VertexBuffer() {
  CHECK_GL_ERROR(glGenBuffers(1, &mID));
}

/**
 * Bind the buffer making the data available for use.
 */
void VertexBuffer::Bind() {
  CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, mID));
}

/**
 * Generate the buffer with the specified data.
 *
 * @param pData             Data to populate into the buffer,
 */
void VertexBuffer::Create(const std::vector<Vertex> &pData) {
  CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, mID));
  CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, pData.size() * sizeof(Vertex), pData.data(), GL_STATIC_DRAW));
}

/**
 * Destroy the buffer in the OpenGL API
 */
void VertexBuffer::Destroy() {
  CHECK_GL_ERROR(glDeleteBuffers(1, &mID));
}
