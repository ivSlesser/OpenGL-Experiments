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
#include "Framework/Renderer.h"

class FrameBuffer {

 private:
  GLuint m_ID = 0;
  GLuint aColor;
  GLuint aDepth;

 public:
  FrameBuffer(unsigned int pWidth, unsigned int pHeight);
  virtual ~FrameBuffer();

  void Bind(unsigned int pWidth, unsigned int pHeight);
  void Bind(GLuint pID, unsigned int pWidth, unsigned int pHeight);

  inline GLuint GetID() { return m_ID; }
  inline void SetID(GLuint to) { m_ID = to; }
  inline GLuint GetColorAttachmentID() { return aColor; }
  inline void SetColorAttachmentID(GLuint to) { aColor = to; }

  inline void BindColorAttachment() {
    CHECK_GL_ERROR(glBindTexture(GL_TEXTURE_2D, aColor));
  }

};
