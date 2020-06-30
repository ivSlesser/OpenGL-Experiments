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


#include <System/Window.h>
#include "FrameBuffer.h"
#include "Renderer.h"

FrameBuffer::FrameBuffer(unsigned W, unsigned H) {
  width = W;
  height = H;
  Generate();
}

FrameBuffer::~FrameBuffer() {
  glDeleteFramebuffers(1, &id);
  glDeleteTextures(1, &aColor);
  glDeleteRenderbuffers(1, &aDepth);
}

void FrameBuffer::Generate() {
  Renderer::ClearGLError();
  glGenFramebuffers((unsigned)1, &id);
  Renderer::CheckGLError("glGenFramebuffers");
  glBindFramebuffer(GL_FRAMEBUFFER, id);
  Renderer::CheckGLError("glBindFramebuffer");

  // Create a colour attachment
  int numberOfChannels = 3;
  GLuint internalFormat = GL_RGB8;
  GLuint format = GL_RGB;

  unsigned char* texels = new unsigned char[width * height * numberOfChannels];

  glGenTextures(1, &aColor);
  glBindTexture(GL_TEXTURE_2D, aColor);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, texels);

  delete[] texels;
  texels = NULL;

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, aColor, 0);

  glGenRenderbuffers(1, &aDepth);
  glBindRenderbuffer(GL_RENDERBUFFER, aDepth);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

  glFramebufferRenderbuffer(
      GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, aDepth
  );

  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cout << "Help!" << std::endl;
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Bind() {
  Renderer::ClearGLError();
  glBindFramebuffer(GL_FRAMEBUFFER, id);
  Renderer::CheckGLError("Bind");

  glViewport(0, 0, width, height);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
}

void FrameBuffer::Unbind() {
  Renderer::ClearGLError();
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  Renderer::CheckGLError("Unbind");

  int w, h;
  glfwGetWindowSize(Window::s_Window, &w, &h);
  glViewport(0, 0, w, h);
  glClear(GL_COLOR_BUFFER_BIT);
  glDisable(GL_DEPTH_TEST);
}
