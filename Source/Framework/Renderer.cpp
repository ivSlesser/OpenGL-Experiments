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
#include "Repository.h"

Renderer *Renderer::s_Instance = nullptr;

Renderer *Renderer::Access() {
  if (s_Instance == nullptr) {
    s_Instance = new Renderer();
  }
  return s_Instance;
}

Renderer::Renderer() {

  // Camera TODO: Integrate into repo
//  GetCamera().SetPosition(0.0f);

  // Default Shader ----------------------------------------------------------------------------------------------------
  Shader shader;
  shader.AddStage(GL_VERTEX_SHADER, "Resources/Shaders/default.vertex.glsl");
  shader.AddStage(GL_FRAGMENT_SHADER, "Resources/Shaders/default.fragment.glsl");
  if (!shader.Compile()) {
    throw std::invalid_argument("Shader compilation failed.");
  }
  Repository::Get()->AddShader("Default", shader);
}

void Renderer::Update(double dt) {
  Renderer::Access()->camera.Update(dt);
}

void Renderer::Draw() {

  Renderer *ptr = Renderer::Access();

  glActiveTexture(GL_TEXTURE0);

  Shader *shader = Repository::Get()->GetShader(); // Default Shader
  shader->Bind();

  shader->Mat4("u_ViewProjection", ptr->camera.GetProjectionView());
  shader->Vec3("u_LightPosition", ptr->mLightPosition);
  shader->Vec3("u_LightColor", ptr->mLightColor);
  shader->Vec3("u_CameraPosition", ptr->camera.GetPosition());

  Renderer::SetupDefaultTexture();

  const std::vector<RenderingInstance> &instances = Repository::Get()->GetAllRenderingInstances();

  for (const RenderingInstance &instance : instances) {

    // Get Components
    Mesh *mesh = Repository::Get()->GetMesh(instance.MeshID);
    Transform *transform = Repository::Get()->GetTransform(instance.TransformID);
    Material *material = Repository::Get()->GetMaterial(instance.MaterialID);

    // Upload Model Matrix
    shader->Mat4("u_Model", transform->Transformation());

    // Upload Material
    material->SubmitAsUniform(shader);

    // Do draw
    mesh->Bind();

    if (mesh->IndexCount != 0) {
      CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, mesh->IndexCount, GL_UNSIGNED_INT, 0));
    } else {
      CHECK_GL_ERROR(glDrawArrays(GL_TRIANGLES, 0, mesh->VertexCount));
    }

  }

}

void Renderer::OnGUI() {
  Renderer *ptr = Renderer::Access();
  ImGui::Begin("Renderer");
  {
    // Texture --------------------------------------------------------------------
    ImGui::Checkbox("Use texture?", &ptr->use_texture);

    // Shader ---------------------------------------------------------------------
    ImGui::ColorEdit3("Light Color", &ptr->mLightColor.x);
    ImGui::DragFloat3("Light Position", &ptr->mLightPosition.x, 1.0f);

    // Camera ---------------------------------------------------------------------
    ImGui::DragFloat3("Camera Position", &ptr->camera.GetPosition().x, -1000.0f, 1000.0f);
    ImGui::DragFloat3("Camera Rotation", &ptr->camera.GetRotation().x, -360.0f, 360.0f);

  }
  ImGui::End();
}
