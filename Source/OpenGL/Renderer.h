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

#include "System/Module.h"
#include "System/Window.h"
#include "Graphics/Properties/Transform.h"
#include "OpenGL/Texture.h"
#include "Graphics/Camera/PerspectiveCamera.h"
#include "Shader.h"

class Renderer {

 private:
  static Renderer *s_Instance;

  PerspectiveCamera camera;

  // Texture Related ---------------------------------------------------------------------------------------------------
  bool use_texture = false;
  Texture white_texture;
  Texture cat_texture = Texture("Resources/Textures/cat.jpg");
  Texture ref_texture = Texture("Resources/Textures/Debug.png");

  // Shader Related ----------------------------------------------------------------------------------------------------
  bool use_lighting = false;
  Shader lit_shader;
  Shader unlit_shader;
  glm::vec3 light_color = glm::vec3(1.0f);
  glm::vec3 light_position = glm::vec3(0.0f, 100.0f, 100.0f);

  // -------------------------------------------------------------------------------------------------------------------

 public:
  static Renderer *Access();
  static void Update(double dt = 1.0);
  static void Draw(Window &window, Transform &transform, Module *module);
  static void OnGUI();

  inline static Camera &GetCamera() { return Renderer::Access()->camera; }

  const glm::vec3 &GetLightColor() const { return light_color; }
  const glm::vec3 &GetLightPosition() const { return light_position; }

 private:
  Renderer();

};
