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

#include "GeometryQuadModule.h"
#include "Math/Random/Random.h"

#include "Graphics/Quad.h"

void GeometryQuadModule::OnInit(Camera &p_Camera) {
  m_Overrides[0] = true;
  p_Camera.SetAndUpdatePosition({0.0f, 0.0f, 3.0f});

  // Create a random color
  glm::vec4 color;
  color.r = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
  color.g = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
  color.b = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
  color.a = 1.0f;

  // Create vertices
  float n = 10.0f;

  for (int i = 0; i < 50; ++i) {
    m_Vertices.push_back({{
                              Random::RandomRange(-n, n),
                              Random::RandomRange(-n, n),
                              0.0f}});
  }

  m_VAO.Bind();
  m_VBO.Init(m_Vertices);
  m_VAO.SetLayout();

  m_Shader.AddStage(GL_VERTEX_SHADER, "Resources/Shaders/geoquad.vertex.glsl");
  m_Shader.AddStage(GL_GEOMETRY_SHADER, "Resources/Shaders/geoquad.geometry.glsl");
  m_Shader.AddStage(GL_FRAGMENT_SHADER, "Resources/Shaders/geoquad.fragment.glsl");
  m_Shader.Compile();
}

void GeometryQuadModule::OnUpdate(double dt) {

}

void GeometryQuadModule::OnDraw(Transform &p_Transform, const Camera &p_Camera) {

  m_Shader.Bind();

  m_Shader.Mat4("u_Model", p_Transform.Transformation());
  m_Shader.Mat4("u_ViewProjection", p_Camera.GetProjectionView());

  m_VAO.Bind();
  glDrawArrays(GL_POINTS, 0, m_Vertices.size());
}
