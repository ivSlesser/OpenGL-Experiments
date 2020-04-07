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

#include "../Modules/TriangleModule.h"
#include "../Modules/QuadModule.h"
#include "../Modules/CubeModule.h"
#include "../Modules/PlaneModule.h"

#include "Externals/stb_image.h"


void Application::Run() {

  gui.Init(window.GetWindow());
  shader.Init("Resources/basic.vertex.glsl", "Resources/basic.fragment.glsl");
  shader.Int("u_Texture0", 0);

  SwitchModule<TriangleModule>();
  module->OnInit(camera);

  gui.AddElement([this]() { ModuleSelector("Module selection:"); });

  while (window.WindowActive()) {

    // Begin -----------------------------------------------------------------------------------------------------------
    window.Begin();

	camera.Update(1.0);
    module->OnUpdate();

    // Draw ------------------------------------------------------------------------------------------------------------
    shader.Bind();

	if (use_texture) {
      cat_texture.Bind();
	} else {
	  white_texture.Bind();
	}

	shader.Mat4("u_Model", transform.Transformation());
    shader.Mat4("u_ViewProjection", camera.GetProjectionView());

    module->OnDraw(shader, camera);

	// GUI
	gui.Render();


    // End ------------------------------------------------------------------------------------------------------------
	window.End();
  }

}

void Application::ModuleSelector(std::string name) {

  ImGui::Begin("General");
  {
    // Texture --------------------------------------------------------------------
    ImGui::Checkbox("Use texture?", &use_texture);
  }
  ImGui::End();

  ImGui::Begin("Transform");
  {
    // Translation ---------------------------------------------------------------
    glm::vec3 translation = transform.GetTranslate();
    ImGui::SliderFloat3("Translation", &translation.x, -10.0f, 10.0f);
    transform.SetTranslate(translation);

    // Rotation ------------------------------------------------------------------
    glm::vec3 rotation = transform.GetRotate();
    ImGui::SliderFloat3("Rotation", &rotation.x, 0.0f, 360.0f);
    transform.SetRotate(rotation);

    // Scale ---------------------------------------------------------------------
    glm::vec3 scale = transform.GetScale();
    ImGui::SliderFloat3("Scale", &scale.x, 0.0f, 10.0f);
    transform.SetScale(scale);
  }
  ImGui::End();

  ImGui::Begin(name.c_str());
  {
	if (ImGui::Button("1. Shape: Triangle")) { SwitchModule<TriangleModule>(); }
	if (ImGui::Button("2. Shape: Quad")) { SwitchModule<QuadModule>(); }
    if (ImGui::Button("3. Shape: Cube")) { SwitchModule<CubeModule>(); }
	if (ImGui::Button("4. Shape: Plane")) { SwitchModule<PlaneModule>(); }
  }
  ImGui::End();

  module->OnGUI();
}
