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
#include "Renderer.h"

class FrameBuffer {

 private:
  unsigned int width, height;
  unsigned int m_ID = 0;
  unsigned int aColor;
  unsigned int aDepth;

 public:
  FrameBuffer() {}
  FrameBuffer(unsigned W, unsigned H);
  virtual ~FrameBuffer();

  void Generate();

  void Bind();
  void Unbind();

  inline unsigned GetID() { return m_ID; }

  inline void BindColorAttachment() {
    Renderer::ClearGLError();
    glBindTexture(GL_TEXTURE_2D, aColor);
    Renderer::CheckGLError("BindColorAttachment");
  }

};
