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


#include "MarchingCubesModule.h"
#include "System/GUI/GUILayer.h"

void MarchingCubesModule::OnInit(Camera &p_Camera) {
  p_Camera.SetAndUpdatePosition({0.0f, 50.0f, 50.0f});
  m_Threshold = m_PrevThresold = 0.01f;
  m_Marcher = new Marcher(glm::vec2(32.0f, 16.0f));
  InternalMarchGrid();
}

void MarchingCubesModule::OnUpdate(double dt) {
  if (m_Threshold != m_PrevThresold) {
    InternalMarchGrid();
    m_PrevThresold = m_Threshold;
  }
}

void MarchingCubesModule::OnDraw(const Shader &p_Shader, const Camera &p_Camera) {
  m_VAO.Bind();
  m_IBO.Bind();
  glDrawElements(GL_TRIANGLES, m_Marcher->IndexCount(), GL_UNSIGNED_INT, 0);
}

void MarchingCubesModule::OnGUI() {
  ImGui::Begin("Marching Cubes Module");
  {
    ImGui::DragFloat("Threshold", &m_Threshold, 0.01f, -1.0f, 1.0f);
  }
  ImGui::End();
}

void MarchingCubesModule::InternalMarchGrid() {
  m_Marcher->March(m_Threshold);

  auto vertices = m_Marcher->Vertices();
  auto indices = m_Marcher->Indices();

  m_VAO.Bind();
  m_VBO.Init(vertices);
  m_VAO.SetLayout();

  m_IBO.Init(indices);
}
