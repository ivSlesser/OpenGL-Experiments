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


#include "MarchingCubesSim.h"
#include "Externals/ImGUI.hpp"

MarchingCubesSim::~MarchingCubesSim() {
}

void MarchingCubesSim::OnCreate() {
  CreateMarchedMesh();
}

void MarchingCubesSim::OnGUI() {

  // Marcher -----------------------------------------------------------------------------------------------------------
  {
    ImGui::Text("Marcher");
    if (ImGui::Button("Generate")) {
      CreateMarchedMesh();
    }
    mMarcher.OnGUI();
  }

  // Material ----------------------------------------------------------------------------------------------------------
  {
    ImGui::Text("Materials");
    for (int i = 0; i < mInstances.size(); ++i) {
      Material *material = Repository::Get()->GetMaterial(Repository::Get()->GetInstance(mInstances[i])->MaterialID);
      material->DisplayWithGUI(i);
      ImGui::NewLine();
    }
  }
}

void MarchingCubesSim::CreateMarchedMesh() {
  mInstances.clear();
  Repository::Get()->ClearMeshes();
  Repository::Get()->ClearInstancesAndTransforms();

  mMarcher.Create();
  Mesh terrainMesh;
  terrainMesh.Create("Marched Terrain Mesh", mMarcher.Vertices(), mMarcher.Indices());
  uint32_t terrain = Repository::Get()->AddMesh(terrainMesh);
  mInstances.push_back(Repository::Get()->AddInstance(terrain, Transform()));
}
