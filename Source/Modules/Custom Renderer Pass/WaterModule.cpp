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
  m_Plane = Plane(color, glm::vec3(0.0f), glm::vec3(50.0f));

  // Create vertices
  m_VAO.Bind();
  m_VBO.Init(m_Plane.Vertices());
  m_VAO.SetLayout();

  // Create indices
  m_IBO.Init(m_Plane.Indices());

//  m_Model.Load("Resources/Models/dragon.obj");

  m_Shader.AddStage(GL_VERTEX_SHADER, "Resources/Shaders/Water/water.vertex.glsl");
  m_Shader.AddStage(GL_FRAGMENT_SHADER, "Resources/Shaders/Water/water.fragment.glsl");
  m_Shader.Compile();
}

void WaterModule::OnUpdate(double dt) {
}

void WaterModule::OnDraw(Transform &p_Transform, const Camera &p_Camera) {

  Renderer *ptr = Renderer::Access();

  m_Shader.Bind();

  m_Shader.Mat4("u_Model", p_Transform.Transformation());
  m_Shader.Mat4("u_ViewProjection", p_Camera.GetProjectionView());

  m_Shader.Vec3("u_LightColor", ptr->GetLightColor());
  m_Shader.Vec3("u_LightPosition", ptr->GetLightPosition());
  m_Shader.Vec3("u_CameraPosition", Renderer::GetCamera().GetPosition());

  m_VAO.Bind();
  m_IBO.Bind();
  glDrawElements(GL_TRIANGLES, m_Plane.IndexCount(), GL_UNSIGNED_INT, 0);

//  m_Model.Bind();
//  glDrawElements(GL_TRIANGLES, m_Model.IndexCount(), GL_UNSIGNED_INT, 0);
}

void WaterModule::OnGUI() {
}

