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


#include "FrameBuffer.h"
#include "System/Window.h"
#include "Framework/Renderer.h"

bool FrameBuffer::Create(uint32_t pWidth, uint32_t pHeight) {
  CHECK_GL_ERROR(glGenFramebuffers(1, &m_ID));
  CHECK_GL_ERROR(glBindFramebuffer(GL_FRAMEBUFFER, m_ID));

  // Create a colour attachment
  CHECK_GL_ERROR(glGenTextures(1, &aColor));
  CHECK_GL_ERROR(glBindTexture(GL_TEXTURE_2D, aColor));
  CHECK_GL_ERROR(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pWidth, pHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 0));
  CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));

  CHECK_GL_ERROR(glGenRenderbuffers(1, &aDepth));
  CHECK_GL_ERROR(glBindRenderbuffer(GL_RENDERBUFFER, aDepth));
  CHECK_GL_ERROR(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, pWidth, pHeight));
  CHECK_GL_ERROR(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, aDepth));

  CHECK_GL_ERROR(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, aColor, 0));

  GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
  CHECK_GL_ERROR(glDrawBuffers(1, DrawBuffers));

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    return false;
  }

  CHECK_GL_ERROR(glBindFramebuffer(GL_FRAMEBUFFER, 0));
  return true;
}

void FrameBuffer::Destroy() {
  if (m_ID != 0) {
    CHECK_GL_ERROR(glDeleteFramebuffers(1, &m_ID));
    CHECK_GL_ERROR(glDeleteTextures(1, &aColor));
    CHECK_GL_ERROR(glDeleteRenderbuffers(1, &aDepth));
  }
}

void FrameBuffer::Bind(const glm::vec2 &pWidthHeight) {
  Bind(pWidthHeight.x, pWidthHeight.y);
}

void FrameBuffer::Bind(uint32_t pWidth, uint32_t pHeight) {
  Bind(m_ID, pWidth, pHeight);
}

void FrameBuffer::Bind(uint32_t pID, const glm::vec2 &pWidthHeight) {
  Bind(pID, pWidthHeight.x, pWidthHeight.y);
}

void FrameBuffer::Bind(uint32_t pID, uint32_t pWidth, uint32_t pHeight) {

#ifdef __APPLE__
  pWidth *= 2;
  pHeight *= 2;
#endif

  CHECK_GL_ERROR(glBindFramebuffer(GL_FRAMEBUFFER, pID));
  CHECK_GL_ERROR(glViewport(0, 0, pWidth, pHeight));
  CHECK_GL_ERROR(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void FrameBuffer::BindColorAttachment() {
  CHECK_GL_ERROR(glBindTexture(GL_TEXTURE_2D, aColor));
}


