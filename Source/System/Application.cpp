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

void Application::Run() {

  gui.Init(window.GetWindow());
  shader.Init("Resources/basic.vertex.glsl", "Resources/basic.fragment.glsl");

  SwitchModule<TriangleModule>();
  module->OnInit();

  gui.AddElement([this]() { ModuleSelector("Module selection:"); });

  while (window.WindowActive()) {
	window.Begin();
	shader.Bind();

	shader.Vec3("u_PickedColor", pickedColor);
	shader.Mat4("u_Model", transform.Transformation());

	module->OnUpdate();

	// GUI
	gui.Render();

	window.End();
  }

}

void Application::ModuleSelector(std::string name) {

  ImGui::Begin("General");
  {
	ImGui::ColorEdit3("General Color", &pickedColor.x);
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
	if (ImGui::Button("1. Triangle")) { SwitchModule<TriangleModule>(); }
	if (ImGui::Button("2. Quad")) { SwitchModule<QuadModule>(); }

  }
  ImGui::End();
}
