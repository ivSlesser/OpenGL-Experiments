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


#include "Renderer.h"
#include "System/GUI/GUILayer.h"

Renderer *Renderer::s_Instance = nullptr;

Renderer *Renderer::Access() {

  if (s_Instance == nullptr) {
	s_Instance = new Renderer();
  }

  return s_Instance;
}

Renderer::Renderer() {
  // Unlit Shader ------------------------------------------------------------------------------------------------------
  unlit_shader.Init("Resources/unlit.basic.vertex.glsl", "Resources/unlit.basic.fragment.glsl");
  unlit_shader.Int("u_Texture0", 0);

  // Lit Shader --------------------------------------------------------------------------------------------------------
  lit_shader.Init("Resources/lit.basic.vertex.glsl", "Resources/lit.basic.fragment.glsl");
  lit_shader.Int("u_Texture0", 0);
}

void Renderer::Update(double dt) {
  Renderer::Access()->camera.Update(dt);
}

void Renderer::Draw(Window &window, Transform &transform, Module *module) {

  Renderer *ptr = Renderer::Access();

  // Draw ------------------------------------------------------------------------------------------------------------
  if (ptr->use_lighting) {
	ptr->lit_shader.Bind();
	ptr->lit_shader.Mat4("u_Model", transform.Transformation());
	ptr->lit_shader.Mat4("u_ViewProjection", ptr->camera.GetProjectionView());
	ptr->lit_shader.Vec3("u_LightPosition", ptr->light_position);
	ptr->lit_shader.Vec3("u_LightColor", ptr->light_color);
	ptr->lit_shader.Vec3("u_CameraPosition", ptr->camera.GetPosition());
  } else {
	ptr->unlit_shader.Bind();
	ptr->unlit_shader.Mat4("u_Model", transform.Transformation());
	ptr->unlit_shader.Mat4("u_ViewProjection", ptr->camera.GetProjectionView());
  }

  if (ptr->use_texture) {
	ptr->cat_texture.Bind();
	if (ptr->cat_texture.HasTransparency()) window.EnableTransparency();
	else window.DisableTransparency();
  } else {
	ptr->white_texture.Bind();
	if (ptr->white_texture.HasTransparency()) window.EnableTransparency();
	else window.DisableTransparency();
  }

  module->OnDraw(ptr->use_lighting ? ptr->lit_shader : ptr->unlit_shader, ptr->camera);
}

void Renderer::OnGUI() {
  Renderer *ptr = Renderer::Access();
  ImGui::Begin("Renderer");
  {
	// Texture --------------------------------------------------------------------
	ImGui::Checkbox("Use texture?", &ptr->use_texture);

	// Shader --------------------------------------------------------------------
	ImGui::Checkbox("Use lit shader?", &ptr->use_lighting);

	if (ptr->use_lighting) {
	  ImGui::ColorEdit3("Light Color", &ptr->light_color.x);
	  ImGui::SliderFloat3("Light Position", &ptr->light_position.x, -100.0f, 100.0f);
	}
  }
  ImGui::End();
}
