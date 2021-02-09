// MIT License
//
// Copyright (c) 2021 Ian Vincent Slesser
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


#include "ToonShadingSim.h"

#include "../../Framework/Geometry/Shapes2D.h"
#include "Externals/ImGUI.hpp"
#include "Framework/Renderer.h"

void ToonShadingSim::OnCreate() {

  // Shader
  Shader shader;
  shader.AddStage(GL_VERTEX_SHADER, "Resources/Shaders/Toon/toon.vertex.glsl");
  shader.AddStage(GL_FRAGMENT_SHADER, "Resources/Shaders/Toon/toon.fragment.glsl");
  shader.Create();
  Renderer::RegisterUniformBuffersToShader(shader.ID());
  uint32_t toonShaderID = Repository::Get()->AddShader("Toon-Shader", shader);

  // Model
  Mesh modelMesh;
  modelMesh.Create("Resources/Models/dragon.obj");
  uint32_t model = Repository::Get()->AddMesh(modelMesh);
  mInstances.push_back(Repository::Get()->AddInstance(model, Transform(), 0, toonShaderID));
}

void ToonShadingSim::OnUpdate() {

}

void ToonShadingSim::OnDestroy() {

}

bool ToonShadingSim::OnGUI() {
  // Material ----------------------------------------------------------------------------------------------------------
  {
	ImGui::Text("Materials");

	for(int i = 0; i < mInstances.size(); ++i) {
	  Material *material = Repository::Get()->GetMaterial(Repository::Get()->GetInstance(mInstances[i])->MaterialID);
	  material->DisplayWithGUI(i);
	  ImGui::NewLine();
	}
  }

  ImGui::DragFloat3("Thresholds", &mThresholds.x, 0.01f, 0.0f, 1.0f, "%.3f");
  ImGui::DragFloat3("Color Damping", &mColorDampers.x, 0.01f, 0.0f, 1.0f, "%.3f");
}

void ToonShadingSim::OnDraw(Shader *pShader) {
  pShader->Vec3("uThresholds", mThresholds);
  pShader->Vec3("uColorDampers", mColorDampers);
}
