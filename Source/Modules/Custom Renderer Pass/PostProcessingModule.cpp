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


#include "PostProcessingModule.h"
#include "Math/Random/Random.h"
#include "System/GUI/GUILayer.h"
#include "OpenGL/Renderer.h"

void PostProcessingModule::OnInit(Camera &p_Camera) {

  m_Overrides[0] = true;
  p_Camera.SetAndUpdatePosition({0.0f, 4.0f, 20.0f});

  // Shaders ---------
  m_Shader.AddStage(GL_VERTEX_SHADER, "Resources/Shaders/GUI/gui.vertex.glsl");
  m_Shader.AddStage(GL_FRAGMENT_SHADER, "Resources/Shaders/GUI/gui.fragment.glsl");
  m_Shader.Compile();

  m_SceneShader.AddStage(GL_VERTEX_SHADER, "Resources/lit.basic.vertex.glsl");
  m_SceneShader.AddStage(GL_FRAGMENT_SHADER, "Resources/lit.basic.fragment.glsl");
  m_SceneShader.Compile();
  m_SceneShader.Int("u_Texture0", 0);

  // Objects ---------
  m_DisplayVAO.Bind();
  m_DisplayVBO.Init(Quad::Vertices(0.0f, 0.0f, 1.0f, 1.0f, glm::vec4(1.0f)));
  m_DisplayVAO.SetLayout();
  m_DisplayIBO.Init(Quad::Indices());

  m_Model.Load("Resources/Models/dragon.obj");

  // Framebuffers ----
  auto dims = Window::GetDimensions();
  int width, height;

#ifdef __APPLE__
  width = dims.x * 2;
  height = dims.y * 2;
#endif
  m_SceneFBO = new FrameBuffer(width, height);
  Window::ToggleFramebufferUsage(true);
}

void PostProcessingModule::OnUpdate(double dt) {

}

void PostProcessingModule::OnDestroy() {
  CHECK_GL_ERROR(glBindFramebuffer(GL_FRAMEBUFFER, 0));
  CHECK_GL_ERROR(glEnable(GL_DEPTH_TEST));
  auto dims = Window::GetDimensions();
  CHECK_GL_ERROR(glViewport(0, 0, dims.x, dims.y));
  Window::ToggleFramebufferUsage(false);
}

void PostProcessingModule::OnGUI() {
  Module::OnGUI();
}

void PostProcessingModule::OnDraw(Transform &p_Transform, const Camera &p_Camera) {
  Renderer *ptr = Renderer::Access();
  CaptureScene(p_Transform, p_Camera);
  DoPostProcessing(p_Transform, p_Camera);
  OutputScene(p_Transform, p_Camera);
}

void PostProcessingModule::CaptureScene(Transform &p_Transform, const Camera &p_Camera) {
  auto dims = Window::GetDimensions();

  Renderer *ptr = Renderer::Access();
  Renderer::SetupDefaultTexture(*Window::s_Instance);

  m_SceneFBO->Bind(dims.x, dims.y);
  m_SceneShader.Bind();

  m_SceneShader.Mat4("u_ViewProjection", p_Camera.GetProjectionView());
  m_SceneShader.Vec3("u_LightColor", ptr->GetLightColor());
  m_SceneShader.Vec3("u_LightPosition", ptr->GetLightPosition());
  m_SceneShader.Vec3("u_CameraPosition", p_Camera.GetPosition());

  // Draw Here
  m_Model.Bind();
  m_SceneShader.Mat4("u_Model", p_Transform.Transformation());
  CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, m_Model.IndexCount(), GL_UNSIGNED_INT, 0));

  m_SceneFBO->Bind(0, dims.x, dims.y);
}

void PostProcessingModule::DoPostProcessing(Transform &p_Transform, const Camera &p_Camera) {

}

void PostProcessingModule::OutputScene(Transform &p_Transform, const Camera &p_Camera) {
  Renderer *ptr = Renderer::Access();

  CHECK_GL_ERROR(glActiveTexture(GL_TEXTURE0));
  m_SceneFBO->BindColorAttachment();

  m_Shader.Bind();
  m_DisplayVAO.Bind();
  m_DisplayIBO.Bind();
  CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, Quad::IndexCount(), GL_UNSIGNED_INT, 0));
}
