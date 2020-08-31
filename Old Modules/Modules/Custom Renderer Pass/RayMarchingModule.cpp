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


#include "RayMarchingModule.h"

#include "Graphics/Quad.h"
#include "System/Window.h"

void RayMarchingModule::OnInit(Camera &p_Camera) {
  m_Overrides[0] = true;
  p_Camera.SetAndUpdatePosition({0.0f, 0.0f, 3.0f});

  // Create vertices
  std::vector<Vertex> vertices = Quad::Vertices(0.0f, 0.0f, 1.0f, 1.0f);
  m_VAO.Bind();
  m_VBO.Init(vertices);
  m_VAO.SetLayout();

  // Create indices
  std::vector<unsigned> indices = Quad::Indices();
  m_IBO.Init(indices);

  m_Shader.AddStage(GL_VERTEX_SHADER, "Resources/Shaders/RayMarch/ray.vertex.glsl");
  m_Shader.AddStage(GL_FRAGMENT_SHADER, "Resources/Shaders/RayMarch/ray.fragment.glsl");
  m_Shader.Compile();
}

void RayMarchingModule::OnUpdate(double dt) {

}

void RayMarchingModule::OnDraw(Transform &p_Transform, const Camera &p_Camera) {
  m_Shader.Bind();
  m_VAO.Bind();
  m_IBO.Bind();

  m_Shader.Vec2("u_Resolution", Window::GetDimensions());
  m_Shader.Float("u_Time", (float)glfwGetTime());

  glDrawElements(GL_TRIANGLES, Quad::IndexCount(), GL_UNSIGNED_INT, 0);
}
