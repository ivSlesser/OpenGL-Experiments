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


#include "GerstnerWaveModule.h"
#include "Math/Random/Random.h"
#include "System/GUI/GUILayer.h"
#include "OpenGL/Renderer.h"

void GerstnerWaveModule::OnInit(Camera &p_Camera) {

  m_Overrides[0] = true;
  p_Camera.SetAndUpdatePosition({3.0f, 1.0f, 7.0f});

  glm::vec4 color = glm::vec4(0.21f, 0.55f, 0.77f, 1.0f);
  plane = Plane(color);

  // Create vertices
  m_VAO.Bind();
  m_VBO.Init(plane.Vertices());
  m_VAO.SetLayout();

  // Create indices
  m_IBO.Init(plane.Indices());

  m_Shader.AddStage(GL_VERTEX_SHADER, "Resources/Shaders/Gerstner/gerstner.vertex.glsl");
  m_Shader.AddStage(GL_FRAGMENT_SHADER, "Resources/Shaders/Gerstner/gerstner.fragment.glsl");
  m_Shader.Compile();
}

void GerstnerWaveModule::OnUpdate(double dt) {
}

void GerstnerWaveModule::OnDraw(Transform &p_Transform, const Camera &p_Camera) {

  Renderer *ptr = Renderer::Access();

  m_Shader.Bind();

  m_Shader.Mat4("u_Model", p_Transform.Transformation());
  m_Shader.Mat4("u_ViewProjection", p_Camera.GetProjectionView());

  m_Shader.Float("u_Time", (float) glfwGetTime());
  m_Shader.Vec4("m_Wave0", m_Wave0);
  m_Shader.Vec4("u_Wave1", m_Wave1);
  m_Shader.Vec4("u_Wave2", m_Wave2);
  m_Shader.Vec4("u_Wave3", m_Wave3);

  m_Shader.Vec3("u_LightPosition", ptr->GetLightPosition());
  m_Shader.Vec3("u_CameraPosition", Renderer::GetCamera().GetPosition());

  m_VAO.Bind();
  m_IBO.Bind();
  glDrawElements(GL_TRIANGLES, plane.IndexCount(), GL_UNSIGNED_INT, 0);
}

void GerstnerWaveModule::OnGUI() {
  ImGui::Text("Wave 0");
  ImGui::DragFloat2("Direction 0", &m_Wave0.x, 0.1f, -1.0f, 1.0f, "%.2f");
  ImGui::DragFloat("Wavelength 0", &m_Wave0.w, 0.1f, 0.0f, 100.0f, "%.2f");
  ImGui::DragFloat("Steepness 0", &m_Wave0.z, 0.01f, 0.0f, 1.0f, "%.3f");

  ImGui::Text("Wave 1");
  ImGui::DragFloat2("Direction 1", &m_Wave1.x, 0.1f, -1.0f, 1.0f, "%.2f");
  ImGui::DragFloat("Wavelength 1", &m_Wave1.w, 0.1f, 0.0f, 100.0f, "%.2f");
  ImGui::DragFloat("Steepness 1", &m_Wave1.z, 0.01f, 0.0f, 1.0f, "%.3f");

  ImGui::Text("Wave 2");
  ImGui::DragFloat2("Direction 2", &m_Wave2.x, 0.1f, -1.0f, 1.0f, "%.2f");
  ImGui::DragFloat("Wavelength 2", &m_Wave2.w, 0.1f, 0.0f, 100.0f, "%.2f");
  ImGui::DragFloat("Steepness 2", &m_Wave2.z, 0.01f, 0.0f, 1.0f, "%.3f");

  ImGui::Text("Wave 3");
  ImGui::DragFloat2("Direction 3", &m_Wave3.x, 0.1f, -1.0f, 1.0f, "%.2f");
  ImGui::DragFloat("Wavelength 3", &m_Wave3.w, 0.1f, 0.0f, 100.0f, "%.2f");
  ImGui::DragFloat("Steepness 3", &m_Wave3.z, 0.01f, 0.0f, 1.0f, "%.3f");
}
