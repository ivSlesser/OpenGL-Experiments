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

#include "Framework/GL/VertexArray.h"
#include "Framework/GL/VertexBuffer.h"
#include "Framework/GL/IndexBuffer.h"
#include "Framework/GL/Shader.h"

#include "Graphics/Plane.h"
#include "Graphics/Model.h"

class FogModule : public Module {
 private:
  Model m_Model;

  Shader m_Shader;

  float m_Density = 0.0035f;
  float m_Gradient = 5.0f;
  glm::vec4 m_SkyColor = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f);

 public:
  FogModule() {}

  virtual void OnInit(Camera &p_Camera) override;
  virtual void OnUpdate(double dt = 1.0) override;
  virtual void OnGUI() override;
  virtual void OnDraw(Transform &p_Transform, const Camera &p_Camera) override;

};
