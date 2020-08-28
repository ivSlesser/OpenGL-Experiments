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

#include "Application.h"

// Default Renderer Pass Modules
#include "Modules/Default Renderer Pass/TriangleModule.h"
#include "Modules/Default Renderer Pass/QuadModule.h"
#include "Modules/Default Renderer Pass/CubeModule.h"
#include "Modules/Default Renderer Pass/PlaneModule.h"
#include "Modules/Default Renderer Pass/ModelModule.h"
#include "Modules/Default Renderer Pass/TerrainModule.h"
#include "Modules/Default Renderer Pass/MarchingCubesModule.h"

// Custom Renderer Pass Modules
#include "Modules/Custom Renderer Pass/GeometryQuadModule.h"
#include "Modules/Custom Renderer Pass/GerstnerWaveModule.h"
#include "Modules/Custom Renderer Pass/FogModule.h"
#include "Modules/Custom Renderer Pass/RayMarchingModule.h"
#include "Modules/Custom Renderer Pass/PostProcessingModule.h"
#include "Modules/Custom Renderer Pass/MaterialModelModule.h"
#include "Modules/Custom Renderer Pass/InstancedModule.h"
#include "Modules/Custom Renderer Pass/TerrainSceneModule.h"

#include "Externals/stb_image.h"

void Application::Init() {
  // Window ------------------------------------------------------------------------------------------------------------
  gui.Init(window.GetWindow());

  // Module ------------------------------------------------------------------------------------------------------------
  SwitchModule<TriangleModule>();
  module->OnInit(Renderer::GetCamera());

  // GUI ---------------------------------------------------------------------------------------------------------------
  gui.AddElement([this]() { ModuleSelector("Module selection:"); });
}

void Application::Run() {

  Init();
  double dt = 1.0;
  while (window.WindowActive()) {
    window.ProcessInput();
    Renderer::Update(dt);
    module->OnUpdate(dt);
    window.Begin();
    Renderer::Draw(window, transform, module);
    gui.Render();
    window.End();
  }
}

void Application::ModuleSelector(std::string name) {

  Renderer::OnGUI();

  ImGui::Begin("General");
  {
    if (ImGui::Checkbox("Wireframe mode?", &mWireframe)) {
      toggleWireframe();
    }
  }
  ImGui::End();

  // ------

  ImGui::Begin("Transform");
  {
    // Translation ---------------------------------------------------------------
    glm::vec3 translation = transform.GetTranslate();
    ImGui::DragFloat3("Translation", &translation.x, -10.0f, 10.0f);
    transform.SetTranslate(translation);

    // Rotation ------------------------------------------------------------------
    glm::vec3 rotation = transform.GetRotate();
    ImGui::DragFloat3("Rotation", &rotation.x, -360.0f, 360.0f);
    transform.SetRotate(rotation);

    // Scale ---------------------------------------------------------------------
    ImGui::DragFloat("Scale (XYZ)", &transform.GetScale().x, 1.0f, 10.0f);
    transform.SetScale(glm::vec3(transform.GetScale().x));
  }
  ImGui::End();

  ImGui::Begin("Module");
  {
    module->OnGUI();
  }
  ImGui::End();

  // ------

  ImGui::Begin(name.c_str());
  {
    if (ImGui::Button("1. Shape: Triangle")) { SwitchModule<TriangleModule>(); }
    if (ImGui::Button("2. Shape: Quad")) { SwitchModule<QuadModule>(); }
    if (ImGui::Button("3. Shape: Cube")) { SwitchModule<CubeModule>(); }
    if (ImGui::Button("4. Shape: Plane")) { SwitchModule<PlaneModule>(); }
    if (ImGui::Button("4. Shape: Model")) { SwitchModule<ModelModule>(); }
    if (ImGui::Button("5. Terrain (Perlin)")) { SwitchModule<TerrainModule>(); }
    if (ImGui::Button("6. Geometry Shader Quads")) { SwitchModule<GeometryQuadModule>(); }
    if (ImGui::Button("7. Marching Cubes")) { SwitchModule<MarchingCubesModule>(); }
    if (ImGui::Button("8. Gerstner Waves (Ocean)")) { SwitchModule<GerstnerWaveModule>(); }
    if (ImGui::Button("9. Fog")) { SwitchModule<FogModule>(); }
    if (ImGui::Button("9. Ray Marching")) { SwitchModule<RayMarchingModule>(); }
    if (ImGui::Button("10. Post Processing")) { SwitchModule<PostProcessingModule>(); }
    if (ImGui::Button("11. Material Model")) { SwitchModule<MaterialModelModule>(); }
    if (ImGui::Button("12. Instanced Model")) { SwitchModule<InstancedModule>(); }
    // TODO: Add to README:
    if (ImGui::Button("13. Terrain Scene")) { SwitchModule<TerrainSceneModule>(); }

  }

  ImGui::End();
}
void Application::toggleWireframe() {
  if (mWireframe) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}

