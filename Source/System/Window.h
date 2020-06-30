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


class Window {
 public:
  static GLFWwindow *s_Window;
  static Window *s_Instance;

 private:
  GLFWwindow *window{nullptr};
  bool is_transparency_enabled = false;
  bool is_left_mouse_held = false;
  bool is_right_mouse_held = false;

  struct WindowConfig {
	unsigned int width = 1366;
	unsigned int height = 768;
	const char *title = "OpenGL Experiments";
	int major = 4;
	int minor = 1;
  } config;


  // -------------------------------------------------------------------------------------------------------------------

 public:
  Window();
  virtual ~Window();

  void Begin();
  void End();

  inline bool WindowActive() { return !glfwWindowShouldClose(window); }
  inline GLFWwindow *GetWindow() { return window; }

  inline static glm::vec2 GetDimensions() { return glm::vec2(s_Instance->config.width, s_Instance->config.height); }

  // Transparency ------------------------------------------------------------------------------------------------------
  inline const bool IsTransparencyEnabled() const { return is_transparency_enabled; }

  // Enables transparency if it is not already enabled.
  inline void EnableTransparency() {
    if (!is_transparency_enabled) {
	  glEnable(GL_BLEND);
	  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
  }

  // Disables transparency if it is not already disabled.
  inline void DisableTransparency() {
    if (is_transparency_enabled) {
      glDisable(GL_BLEND);
    }
  }

  // Callbacks ---------------------------------------------------------------------------------------------------------
  void ProcessInput();
  static void OnResize(GLFWwindow *window, int width, int height);
  static void OnMouseMove(GLFWwindow* window, double xpos, double ypos);
  static void OnMouseButton(GLFWwindow *m, int button, int action, int mods);

};

