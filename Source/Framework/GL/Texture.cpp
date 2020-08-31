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

/**
 * Creates a 1x1 white texture.
 *
 *
 * @param pName            Texture name.
 * @return                  True if created successfully.
*/
bool Texture::Create(std::string &pName) {
  mName = pName;

  if (mID == 0) {
    CHECK_GL_ERROR(glGenTextures(1, &mID));
  }
  CHECK_GL_ERROR(glBindTexture(GL_TEXTURE_2D, mID));

  CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

  unsigned int data = 0xffffffff;
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data);

  return true;
}

/**
 * Creates a texture from a file.
 *
 * @param pName             Texture name.
 * @param pFile             Texture source file.
 * @return                  True if created successfully.
 */
bool Texture::Create(std::string &pName, const char *pFile) {
  mName = pName;
  // Load a texture from a file.
  if (mID == 0) {
    CHECK_GL_ERROR(glGenTextures(1, &mID));
  }
  CHECK_GL_ERROR(glBindTexture(GL_TEXTURE_2D, mID));

  CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  CHECK_GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(pFile, &width, &height, &nrChannels, 0);
  if (data) {
    // Check if transparency ( channel )
    GLenum format = nrChannels == 3 ? GL_RGB : GL_RGBA;
    mHasAlpha = nrChannels == 3;
    // Create texture
    CHECK_GL_ERROR(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data))
    CHECK_GL_ERROR(glGenerateMipmap(GL_TEXTURE_2D))
  } else {
    std::cout << "Failed to load texture" << std::endl;
    return false;
  }
  stbi_image_free(data);
  return true;
}

/**
 * Used to remove the texture from the OpenGL API
 */
void Texture::Destroy() {
  CHECK_GL_ERROR(glDeleteTextures(1, &mID));
  mID = 0;
}

/**
 * Binds the texture so it is active for use.
 */
void Texture::Bind() {
  CHECK_GL_ERROR(glBindTexture(GL_TEXTURE_2D, mID));
}