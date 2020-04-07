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

#include "TriangleModule.h"
#include "../Graphics/Triangle.h"

void TriangleModule::OnInit(Camera &camera) {

  camera.SetAndUpdatePosition({0.0f, 0.0f, 3.0f});

  // Create a random color
  glm::vec4 color;
  color.r = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
  color.g = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
  color.b = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
  color.a = 1.0f;

  // Create vertices
  std::vector<Vertex> vertices = Triangle::Vertices(color);
  VAO.Bind();
  VBO.Init(vertices);
  VAO.SetLayout();
}

void TriangleModule::OnUpdate(double dt) {

}

void TriangleModule::OnDraw(const Shader &shader, const Camera &camera) {
  VAO.Bind();
  glDrawArrays(GL_TRIANGLES, 0, Triangle::VertexCount());
}
