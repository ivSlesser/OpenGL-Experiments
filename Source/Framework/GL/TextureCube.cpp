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


#include "TextureCube.h"

#include "Externals/stb_image.h"
#include "Framework/Renderer.h"

TextureCube::~TextureCube() {
  CHECK_GL_ERROR(glDeleteTextures(1, &m_ID));
}

bool TextureCube::Init(std::vector<const char *> pFaces) {
  if (m_ID == 0) {
    CHECK_GL_ERROR(glGenTextures(1, &m_ID));
  }
  CHECK_GL_ERROR(glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID));

  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(false);
  for (unsigned int i = 0; i < pFaces.size(); i++) {
    unsigned char *data = stbi_load(pFaces[i], &width, &height, &nrChannels, 0);
    if (data) {
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                   0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
      );
      stbi_image_free(data);
    } else {
      std::cout << "Failed to load cube map: " << pFaces[i] << std::endl;
      stbi_image_free(data);
      return false;
    }
  }
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  return true;
}

void TextureCube::Bind() {
  CHECK_GL_ERROR(glActiveTexture(GL_TEXTURE0));
  CHECK_GL_ERROR(glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID));

}
