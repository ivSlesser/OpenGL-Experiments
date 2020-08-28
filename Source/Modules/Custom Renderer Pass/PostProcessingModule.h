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
#include "Framework/GL/FrameBuffer.h"
#include "Framework/GL/Shader.h"

#include "Graphics/Plane.h"
#include "Graphics/Quad.h"
#include "Graphics/Model.h"

class PostProcessingModule : public Module {

 private:
  VertexArray m_DisplayVAO;
  VertexBuffer m_DisplayVBO;
  IndexBuffer m_DisplayIBO;

  VertexArray  m_SceneVAO;
  VertexBuffer m_SceneVBO;
  IndexBuffer  m_SceneIBO;
  FrameBuffer *m_SceneFBO;

  Shader m_Shader;
  Shader m_SceneShader;

  Model m_Model;

  bool m_Greyscale = false;
  bool m_Invert = false;
  bool m_Contrast = true;

  float m_ContrastStrength = 0.6f;

 public:
  PostProcessingModule() {}

  virtual void OnInit(Camera &p_Camera) override;
  virtual void OnUpdate(double dt = 1.0) override;
  void OnDestroy() override;
  virtual void OnGUI() override;
  virtual void OnDraw(Transform &p_Transform, const Camera &p_Camera) override;

 private:
  void CaptureScene(Transform &p_Transform, const Camera &p_Camera);
  void OutputScene(Transform &p_Transform, const Camera &p_Camera);

};
