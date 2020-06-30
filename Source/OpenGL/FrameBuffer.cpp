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

FrameBuffer::FrameBuffer(unsigned W, unsigned H) {
  Generate();
}

FrameBuffer::~FrameBuffer() {
  glDeleteFramebuffers(1, &id);
  glDeleteTextures(1, &aColor);
  glDeleteTextures(1, &aDepth);
}

void FrameBuffer::Generate() {
  if (id) {
    glDeleteFramebuffers(1, &id);
    glDeleteTextures(1, &aColor);
    glDeleteTextures(1, &aDepth);
  }

  glCreateFramebuffers(1, &id);
  glBindFramebuffer(GL_FRAMEBUFFER, id);

  // Create a colour attachment
  glCreateTextures(GL_TEXTURE_2D, 1, &aColor);
  glBindTexture(GL_TEXTURE_2D, aColor);
  // GL_RGBA16F or GL_RGBA32F would be for HDR
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, aColor, 0);

  // Depth attachment
  glCreateTextures(GL_TEXTURE_2D, 1, &aDepth);
  glBindTexture(GL_TEXTURE_2D, aDepth);
  glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, width, height);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, aDepth, 0);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Resize(unsigned W, unsigned H) {
  width = W;
  height = H;
  Generate();
}

void FrameBuffer::Bind() {
  glBindFramebuffer(GL_FRAMEBUFFER, id);
  glViewport(0, 0, width, height);
}

void FrameBuffer::Unbind() {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
