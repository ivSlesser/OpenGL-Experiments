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


#include "CubeModule.h"

#include "Graphics/Cube.h"
#include "../../FlatCube.h"

#include "System/GUI/GUILayer.h"

void CubeModule::OnInit(Camera &p_Camera) {

  p_Camera.SetAndUpdatePosition({0.0f, 0.0f, 3.0f});
  GenerateMesh();
}

void CubeModule::OnUpdate(double dt) {
}

void CubeModule::OnDraw(const Shader &p_Shader, const Camera &p_Camera) {
  m_VAO.Bind();

  if (m_UseFlat) {
	glDrawArrays(GL_TRIANGLES, 0, FlatCube::VertexCount());
  } else {
	m_IBO.Bind();
	glDrawElements(GL_TRIANGLES, Cube::IndexCount(), GL_UNSIGNED_INT, 0);
  }
}

void CubeModule::OnGUI() {
  if (ImGui::Button("Toggle Cube / Flat Cube")) {
	m_UseFlat = !m_UseFlat;
	GenerateMesh();
  }
}

void CubeModule::GenerateMesh() {
  // Create a random color
  glm::vec4 color;
  color.r = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
  color.g = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
  color.b = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
  color.a = 1.0f;

  std::vector<Vertex> vertices;

  if (m_UseFlat) {
	vertices = FlatCube::Vertices(color);
  } else {
	vertices = Cube::Vertices(color);
	std::vector<unsigned> indices = Cube::Indices();
	m_IBO.Init(indices);
  }

  m_VAO.Bind();
  m_VBO.Init(vertices);
  m_VAO.SetLayout();
}
