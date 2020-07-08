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

#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/FrameBuffer.h"
#include "OpenGL/Shader.h"

#include "Graphics/Plane.h"
#include "Graphics/Quad.h"
#include "Graphics/Model.h"

class WaterModule : public Module {

 private:
  VertexArray m_VAO;
  VertexBuffer m_VBO;
  IndexBuffer m_IBO;
  FrameBuffer *m_FBOReflection;
  FrameBuffer *m_FBORefraction;

  Plane m_Plane;
  Shader m_Shader;
  Shader m_GUIShader;

  Model m_Model;

  VertexArray m_QVAOA;
  VertexBuffer m_QVBOA;
  IndexBuffer m_QIBOA;

  VertexArray m_QVAOB;
  VertexBuffer m_QVBOB;
  IndexBuffer m_QIBOB;

 public:
  WaterModule() {}

  virtual void OnInit(Camera &p_Camera) override;
  virtual void OnUpdate(double dt = 1.0) override;
  void OnDestroy() override;
  virtual void OnGUI() override;
  virtual void OnDraw(Transform &p_Transform, const Camera &p_Camera) override;

 private:
  void PrimaryRenderPass(Transform &p_Transform, const Camera &p_Camera);
  void GUIRenderPass(Transform &p_Transform, const Camera &p_Camera, FrameBuffer *p_FBO, bool pReflection);
};
