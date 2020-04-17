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

#include "OpenGL/Shader.h"
#include "OpenGL/Texture.h"
#include "Graphics/Properties/Transform.h"

#include "Graphics/Camera/Camera.h"

class Module {
 protected:
  bool m_Overrides[1] = {false}; // 0: Shader

  // -------------------------------------------------------------------------------------------------------------------
 public:
  virtual ~Module() {}
  virtual void OnInit(Camera &p_Camera) = 0;
  virtual void OnUpdate(double dt = 1.0) = 0;
  virtual void OnGUI() {}

  virtual void OnDraw(const Shader &p_Shader, const Camera &p_Camera) {}
  virtual void OnDraw(Transform &p_Transform, const Camera &p_Camera) {} // Called when overriding renderer's shader.

  inline const bool OverridesShader() const { return m_Overrides[0]; }
};
