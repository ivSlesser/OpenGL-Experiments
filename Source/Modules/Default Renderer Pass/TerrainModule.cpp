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


#include "TerrainModule.h"

void TerrainModule::OnInit(Camera &camera) {
  camera.SetAndUpdatePosition({3.0f, 1.0f, 7.0f});

  // Create a random color
  glm::vec4 color;
  color.r = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
  color.g = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
  color.b = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
  color.a = 1.0f;

  terrain = Terrain(color, glm::vec3(0.0f), glm::vec2(100.0f), 1);

  // Create vertices
  VAO.Bind();
  VBO.Init(terrain.Vertices());
  VAO.SetLayout();

  // Create indices
  IBO.Init(terrain.Indices());
}

void TerrainModule::OnUpdate(double dt) {

}

void TerrainModule::OnDraw(const Shader &shader, const Camera &camera) {
  VAO.Bind();
  IBO.Bind();
  glDrawElements(GL_TRIANGLES, terrain.IndexCount(), GL_UNSIGNED_INT, 0);
}
