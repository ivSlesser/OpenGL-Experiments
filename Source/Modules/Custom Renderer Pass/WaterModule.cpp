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


#include "WaterModule.h"
#include "Math/Random/Random.h"
#include "System/GUI/GUILayer.h"
#include "OpenGL/Renderer.h"

void WaterModule::OnInit(Camera &p_Camera) {

  m_Overrides[0] = true;
  p_Camera.SetAndUpdatePosition({3.0f, 1.0f, 7.0f});

  glm::vec4 color = glm::vec4(0.21f, 0.55f, 0.77f, 1.0f);
  m_Plane = Plane(color);

  // Create vertices
  m_VAO.Bind();
  m_VBO.Init(m_Plane.Vertices());
  m_VAO.SetLayout();

  // Create indices
  m_IBO.Init(m_Plane.Indices());

  m_Model.Load("Resources/Models/dragon.obj");

  m_Shader.AddStage(GL_VERTEX_SHADER, "Resources/Shaders/Water/water.vertex.glsl");
  m_Shader.AddStage(GL_FRAGMENT_SHADER, "Resources/Shaders/Water/water.fragment.glsl");
  m_Shader.Compile();

  auto dims = Window::GetDimensions();
  int width, height;

#ifdef __APPLE__
  width = dims.x * 2;
  height = dims.y * 2;
#endif

  m_FBO = new FrameBuffer(width, height);

  Window::ToggleFramebufferUsage(true);

  // Quad
  m_QVAO.Bind();
  m_QVBO.Init(Quad::Vertices(0.0f, 0.0f, 10.0f, 10.0f, glm::vec4(1.0f)));
  m_QVAO.SetLayout();
  m_QIBO.Init(Quad::Indices());
}

void WaterModule::OnUpdate(double dt) {
}

void WaterModule::OnDraw(Transform &p_Transform, const Camera &p_Camera) {

  Renderer *ptr = Renderer::Access();

  auto dims = Window::GetDimensions();
  int w, h;
  w = dims.x;
  h = dims.y;

#ifdef __APPLE__
  w *= 2;
  h *= 2;
#endif

  m_FBO->Bind();
  glViewport(0, 0, w, h);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  Renderer::SetupDefaultTexture(*Window::s_Instance);

  m_Shader.Bind();

  m_Shader.Mat4("u_ViewProjection", p_Camera.GetProjectionView());
  m_Shader.Vec3("u_LightColor", ptr->GetLightColor());
  m_Shader.Vec3("u_LightPosition", ptr->GetLightPosition());
  m_Shader.Vec3("u_CameraPosition", Renderer::GetCamera().GetPosition());

  // Above Water
  m_Model.Bind();
  Transform modelTF;
  modelTF.SetScale(glm::vec3(0.5f));
  modelTF.SetTranslate(glm::vec3(5.0f, 1.0f, 5.0f));
  m_Shader.Mat4("u_Model", modelTF.Transformation());
  glDrawElements(GL_TRIANGLES, m_Model.IndexCount(), GL_UNSIGNED_INT, 0);

  // Under Water
  modelTF.SetScale(glm::vec3(0.5f));
  modelTF.SetTranslate(glm::vec3(40.0f, -10.0f, 40.0f));
  m_Shader.Mat4("u_Model", modelTF.Transformation());
  glDrawElements(GL_TRIANGLES, m_Model.IndexCount(), GL_UNSIGNED_INT, 0);

  // Water
  m_Shader.Mat4("u_Model", p_Transform.Transformation());
  m_VAO.Bind();
  m_IBO.Bind();
  glDrawElements(GL_TRIANGLES, m_Plane.IndexCount(), GL_UNSIGNED_INT, 0);

  m_FBO->Unbind();
  glViewport(0, 0, w, h);
  glClear(GL_COLOR_BUFFER_BIT);
  glDisable(GL_DEPTH_TEST);

  m_FBO->BindColorAttachment();

  m_Shader.Mat4("u_Model", p_Transform.Transformation());
  m_QVAO.Bind();
  m_QIBO.Bind();
  glDrawElements(GL_TRIANGLES, m_Quad.IndexCount(), GL_UNSIGNED_INT, 0);
}

void WaterModule::OnGUI() {
  ImGui::Image((void*)(intptr_t)m_FBO->GetColorAttachmentID(), ImVec2(256.0f, 256.0f));
}

void WaterModule::OnDestroy() {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glEnable(GL_DEPTH_TEST);
  auto dims = Window::GetDimensions();
  glViewport(0, 0, dims.x, dims.y);
  Window::ToggleFramebufferUsage(false);
}

