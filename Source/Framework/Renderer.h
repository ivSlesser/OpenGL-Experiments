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

#define DEBUG_ONLY(x)   x;

#define CHECK_GL_ERROR(x)   Renderer::ClearGLError();     \
                            x;                            \
                            Renderer::CheckGLError(#x);

#include "Common.h"

#include "System/Window.h"
#include "Framework/Components/Transform.h"
#include "Framework/GL/Texture.h"
#include "./Components/Camera/PerspectiveCamera.h"
#include "Framework/GL/Shader.h"

class Renderer {

 private:
  static Renderer *s_Instance;

  struct RenderingStatistics {
    uint32_t Calls = 0;
    uint32_t Vertices = 0;
    uint32_t Indices = 0;
  } mStatistics;                                      // Collected statistics for the renderer.

  PerspectiveCamera camera;                           // Camera (Will refactor into repo)
  bool mIsWireframeEnabled = false;                   // Is the wire-frame mode enabled?

  glm::vec3 mClearColor = glm::vec3(0.474f);  // Clear color for the buffer swap routine.

  // Texture Related ---------------------------------------------------------------------------------------------------

  // TODO: Add Textures To Repo
//  Texture cat_texture = Texture("Resources/Textures/cat.jpg");
//  Texture ref_texture = Texture("Resources/Textures/Debug.png");

  // Shader Related ----------------------------------------------------------------------------------------------------
  glm::vec3 mLightColor = glm::vec3(1.0f);
  glm::vec3 mLightPosition = glm::vec3(1000.0f, 1000.0f, 1000.0f);

  // -------------------------------------------------------------------------------------------------------------------

 public:
  static Renderer *Access();
  static void Begin();
  static void End();
  static void Draw();
  static void OnGUI();

  static void ToggleWireframeRendering();

  inline static Camera &GetCamera() { return Renderer::Access()->camera; }
  inline const glm::vec3 &GetLightColor() const { return mLightColor; }
  inline const glm::vec3 &GetLightPosition() const { return mLightPosition; }

  /**
   * Utility function to clear all OpenGL errors.
   */
  static void ClearGLError() {
    unsigned errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR) {
    }
  }

  /**
   * Utility function to check if there is an error flaged by the
   * OpenGL API.
   *
   * @param msg             [Optional] Message to prepend to error check output.
   */
  static void CheckGLError(std::string msg = "") {
    auto res = glGetError();
    if (res != 0) {
      std::cout << msg << " -> " << res << std::endl;
    }
  }

 private:
  Renderer();
};
