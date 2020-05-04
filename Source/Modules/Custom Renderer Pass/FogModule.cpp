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


#include "FogModule.h"
#include "Math/Random/Random.h"
#include "System/GUI/GUILayer.h"
#include "OpenGL/Renderer.h"

void FogModule::OnInit(Camera &p_Camera) {

  m_Overrides[0] = true;
  p_Camera.SetAndUpdatePosition({0.0f, 0.0f, 3.0f});
  m_Model.Load("Resources/Models/dragon.obj");

  m_Shader.AddStage(GL_VERTEX_SHADER, "Resources/Shaders/Fog/fog.vertex.glsl");
  m_Shader.AddStage(GL_FRAGMENT_SHADER, "Resources/Shaders/Fog/fog.fragment.glsl");
  m_Shader.Compile();
}

void FogModule::OnUpdate(double dt) {
}

void FogModule::OnDraw(Transform &p_Transform, const Camera &p_Camera) {

  Renderer *ptr = Renderer::Access();

  m_Shader.Bind();

  m_Shader.Mat4("u_Model", p_Transform.Transformation());
  m_Shader.Mat4("u_View", p_Camera.GetView());
  m_Shader.Mat4("u_Projection", p_Camera.GetProjection());

  m_Shader.Float("u_Time", (float) glfwGetTime());
  m_Shader.Vec3("u_LightPosition", ptr->GetLightPosition());
  m_Shader.Vec3("u_CameraPosition", Renderer::GetCamera().GetPosition());
  m_Shader.Vec4("u_SkyColor", m_SkyColor);

  m_Shader.Float("u_Density", m_Density);
  m_Shader.Float("u_Gradient", m_Gradient);

  m_Model.Bind();
  glDrawElements(GL_TRIANGLES, m_Model.IndexCount(), GL_UNSIGNED_INT, 0);
}

void FogModule::OnGUI() {
  ImGui::DragFloat("Density", &m_Density, 0.001f, 0.0f, 1.0f);
  ImGui::DragFloat("Gradient", &m_Gradient, 0.01f, 0.0f, 4.0f);
  ImGui::ColorPicker4("Sky Color", &m_SkyColor.x);
}
