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

#include "Texture.h"

#include "Externals/stb_image.h"
#include "Framework/Renderer.h"

unsigned int Texture::slot_incrementor = 0;

Texture::Texture() {

  // Create a default white texture.
  if (id == 0) {
    CHECK_GL_ERROR(glGenTextures(1, &id));
  }
  CHECK_GL_ERROR(glBindTexture(GL_TEXTURE_2D, id));

  CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

  unsigned int data = 0xffffffff;
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data);
}

Texture::Texture(const char *file) {

  // Load a texture from a file.
  if (id == 0) {
    CHECK_GL_ERROR(glGenTextures(1, &id));
  }
  CHECK_GL_ERROR(glBindTexture(GL_TEXTURE_2D, id));

  CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(file, &width, &height, &nrChannels, 0);
  if (data)
  {
    // Check if transparency ( channel )
    GLenum format = nrChannels == 3 ? GL_RGB : GL_RGBA;
    transparency = nrChannels == 3;

    // Create texture
    CHECK_GL_ERROR(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data))
    CHECK_GL_ERROR(glGenerateMipmap(GL_TEXTURE_2D))

  }
  else
  {
    std::cout << "Failed to load texture" << std::endl;
  }

  stbi_image_free(data);
}

Texture::~Texture() {
  CHECK_GL_ERROR(glDeleteTextures(1, &id));
}

void Texture::Bind() {
  CHECK_GL_ERROR(glBindTexture(GL_TEXTURE_2D, id));
}

GLenum Texture::SlotIntToEnum() {
  switch(slot) {
    case 0: return GL_TEXTURE0;
    case 1: return GL_TEXTURE1;
    case 2: return GL_TEXTURE2;
    case 3: return GL_TEXTURE3;
    default: return GL_TEXTURE0;
  }
}
