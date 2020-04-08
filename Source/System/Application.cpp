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
#include "../Modules/ModelModule.h"

#include "Externals/stb_image.h"

void Application::Init() {
  // Window ------------------------------------------------------------------------------------------------------------
  gui.Init(window.GetWindow());

  // Unlit Shader ------------------------------------------------------------------------------------------------------
  unlit_shader.Init("Resources/unlit.basic.vertex.glsl", "Resources/unlit.basic.fragment.glsl");
  unlit_shader.Int("u_Texture0", 0);

  // Lit Shader --------------------------------------------------------------------------------------------------------
  lit_shader.Init("Resources/lit.basic.vertex.glsl", "Resources/lit.basic.fragment.glsl");
  lit_shader.Int("u_Texture0", 0);

  // Module ------------------------------------------------------------------------------------------------------------
  SwitchModule<TriangleModule>();
  module->OnInit(camera);

  // GUI ---------------------------------------------------------------------------------------------------------------
  gui.AddElement([this]() { ModuleSelector("Module selection:"); });
}

void Application::Run() {

  Init();

  while (window.WindowActive()) {

	// Begin -----------------------------------------------------------------------------------------------------------
	window.Begin();

	camera.Update(1.0);
	module->OnUpdate();

	// Draw ------------------------------------------------------------------------------------------------------------
	if (use_lighting) {
	  lit_shader.Bind();
	  lit_shader.Mat4("u_Model", transform.Transformation());
	  lit_shader.Mat4("u_ViewProjection", camera.GetProjectionView());
	  lit_shader.Vec3("u_LightPosition", light_position);
	  lit_shader.Vec3("u_LightColor", light_color);
	  lit_shader.Vec3("u_CameraPosition", camera.GetPosition());
	} else {
	  unlit_shader.Bind();
	  unlit_shader.Mat4("u_Model", transform.Transformation());
	  unlit_shader.Mat4("u_ViewProjection", camera.GetProjectionView());
	}

	if (use_texture) {

	  cat_texture.Bind();
	  if (cat_texture.HasTransparency())
	    window.EnableTransparency();
	  else
	    window.DisableTransparency();

	} else {
	  white_texture.Bind();
	  if (white_texture.HasTransparency())
	    window.EnableTransparency();
	  else
	    window.DisableTransparency();

	}

	module->OnDraw(use_lighting ? lit_shader : unlit_shader, camera);

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
	// Shader --------------------------------------------------------------------
	ImGui::Checkbox("Use lit shader?", &use_lighting);

	if (use_lighting) {
	  ImGui::ColorEdit3("Light Color", &light_color.x);
	  ImGui::SliderFloat3("Light Position", &light_position.x, -100.0f, 100.0f);
	}

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
//	glm::vec3 scale = transform.GetScale();
	//ImGui::SliderFloat3("Scale", &scale.x, 0.0f, 10.0f);
	float scale_float = transform.GetScale().x;
	ImGui::SliderFloat("Scale (XYZ)", &scale_float, 1.0f, 10.0f);
	glm::vec3 scale = glm::vec3(scale_float);
	transform.SetScale(scale);
  }
  ImGui::End();

  ImGui::Begin(name.c_str());
  {
	if (ImGui::Button("1. Shape: Triangle")) { SwitchModule<TriangleModule>(); }
	if (ImGui::Button("2. Shape: Quad")) { SwitchModule<QuadModule>(); }
	if (ImGui::Button("3. Shape: Cube")) { SwitchModule<CubeModule>(); }
	if (ImGui::Button("4. Shape: Plane")) { SwitchModule<PlaneModule>(); }
	if (ImGui::Button("4. Shape: Model")) { SwitchModule<ModelModule>(); }
  }
  ImGui::End();

  module->OnGUI();
}

