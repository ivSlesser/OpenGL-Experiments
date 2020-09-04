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


#include "GerstnerWaveSim.h"
#include "../../Framework/Geometry/Shapes2D.h"
#include "../../Framework/Geometry/Shapes3D.h"
#include "Externals/ImGUI.hpp"

GerstnerWaveSim::~GerstnerWaveSim() {

}

void GerstnerWaveSim::OnCreate() {

  // Shader
  Shader ppShader;
  ppShader.AddStage(GL_VERTEX_SHADER, "Resources/Shaders/Gerstner/gerstner.vertex.glsl");
  ppShader.AddStage(GL_FRAGMENT_SHADER, "Resources/Shaders/Gerstner/gerstner.fragment.glsl");
  ppShader.Create();
  mGerstnerShaderID = Repository::Get()->AddShader("Gerstner-Waves", ppShader);

  // Material
  Material sea;
  sea.Name = "Ocean";
  sea.Diffuse = glm::vec3(0.0f, 0.412f, 0.58f);
  uint32_t seaMaterialID = Repository::Get()->AddMaterial(sea);

  Plane p;
  p.Create(glm::vec2(100.0f), 2.0f);

  Mesh planeMesh;
  planeMesh.Create("Water Plane", p.Vertices(), p.Indices());
  uint32_t plane = Repository::Get()->AddMesh(planeMesh);
  Transform t;
  t.SetRotate({-10.0f, 0.0f, 0.0f});
  mInstances.push_back(Repository::Get()->AddInstance(plane, t, seaMaterialID, mGerstnerShaderID));
}

void GerstnerWaveSim::OnUpdate() {
}

void GerstnerWaveSim::OnFixedUpdate(const double &pStep) {

}

void GerstnerWaveSim::OnPreDraw() {
  Shader *shader = Repository::Get()->GetShader(mGerstnerShaderID);
  shader->Bind();

  shader->Vec4("u_Wave0", mWave0);
  shader->Vec4("u_Wave1", mWave1);
  shader->Vec4("u_Wave2", mWave2);
}

void GerstnerWaveSim::OnDestroy() {

}

void GerstnerWaveSim::OnGUI() {
  ImGui::Text("Wave 0");
  ImGui::DragFloat2("Direction 0", &mWave0.x, 0.1f, -1.0f, 1.0f, "%.2f");
  ImGui::DragFloat("Wavelength 0", &mWave0.w, 0.1f, 0.0f, 100.0f, "%.2f");
  ImGui::DragFloat("Steepness 0", &mWave0.z, 0.01f, 0.0f, 1.0f, "%.3f");

  ImGui::Text("Wave 1");
  ImGui::DragFloat2("Direction 1", &mWave1.x, 0.1f, -1.0f, 1.0f, "%.2f");
  ImGui::DragFloat("Wavelength 1", &mWave1.w, 0.1f, 0.0f, 100.0f, "%.2f");
  ImGui::DragFloat("Steepness 1", &mWave1.z, 0.01f, 0.0f, 1.0f, "%.3f");

  ImGui::Text("Wave 2");
  ImGui::DragFloat2("Direction 2", &mWave2.x, 0.1f, -1.0f, 1.0f, "%.2f");
  ImGui::DragFloat("Wavelength 2", &mWave2.w, 0.1f, 0.0f, 100.0f, "%.2f");
  ImGui::DragFloat("Steepness 2", &mWave2.z, 0.01f, 0.0f, 1.0f, "%.3f");

  // Material ----------------------------------------------------------------------------------------------------------
  {
    // TODO: Reset Material
    ImGui::Text("Materials");
    for(int i = 0; i < mInstances.size(); ++i) {
      Material *material = Repository::Get()->GetMaterial(Repository::Get()->GetInstance(mInstances[i])->MaterialID);
      material->DisplayWithGUI(i);
      ImGui::NewLine();
    }
  }

}

