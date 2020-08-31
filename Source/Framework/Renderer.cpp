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

/**
 * Return a pointer to the singleton instance of the renderer, creating
 * it if the renderer is not already setup.
 *
 * @return                  Pointer to renderer singleton instance
 */
Renderer *Renderer::Access() {
  if (s_Instance == nullptr) {
    s_Instance = new Renderer();
  }
  return s_Instance;
}

/**
 * Constructor, handles creation of a default shader.
 */
Renderer::Renderer() {

  // Camera TODO: Integrate into repo
//  GetCamera().SetPosition(0.0f);
}

/**
 * Performs rendering functions, setting shader variables and querying the repository for rendering instances.
 * Will load the values defined in each instance before rendering the actual geometry.
 */
void Renderer::Draw() {

  Renderer *ptr = Renderer::Access();
  glActiveTexture(GL_TEXTURE0);

  Shader *shader = Repository::Get()->GetShader(); // Default Shader
  shader->Bind();

  shader->Mat4("u_ViewProjection", ptr->camera.GetProjectionView());
  shader->Vec3("u_LightPosition", ptr->mLightPosition);
  shader->Vec3("u_LightColor", ptr->mLightColor);
  shader->Vec3("u_CameraPosition", ptr->camera.GetPosition());

  const std::vector<RenderingInstance> &instances = Repository::Get()->GetAllRenderingInstances();

  for (const RenderingInstance &instance : instances) {

    // Get Components
    Mesh *mesh = Repository::Get()->GetMesh(instance.MeshID);
    Transform *transform = Repository::Get()->GetTransform(instance.TransformID);
    Material *material = Repository::Get()->GetMaterial(instance.MaterialID);
    Texture *texture = Repository::Get()->GetTexture(instance.TextureID); // TODO: Also need to check for alpha.

    // Upload Model Matrix
    shader->Mat4("u_Model", transform->Transformation());

    // Upload Material
    material->SubmitAsUniform(shader);

    // Do draw
    mesh->Bind();

    DEBUG_ONLY(s_Instance->mStatistics.Calls++)

    if (mesh->IndexCount != 0) {
      DEBUG_ONLY(s_Instance->mStatistics.Indices += mesh->IndexCount)
      CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, mesh->IndexCount, GL_UNSIGNED_INT, 0));
    } else {
      DEBUG_ONLY(s_Instance->mStatistics.Vertices += mesh->VertexCount)
      CHECK_GL_ERROR(glDrawArrays(GL_TRIANGLES, 0, mesh->VertexCount));
    }
  }
}

/**
 * Displays the renderer data and controls.
 */
void Renderer::OnGUI() {
  Renderer *ptr = Renderer::Access();
  ImGui::Begin("Renderer");
  {
    // Statistics ------------------------------------------------------------------------------------------------------
    DEBUG_ONLY(ImGui::Text("Draw Calls: %d", s_Instance->mStatistics.Calls))
    DEBUG_ONLY(ImGui::Text("Vertices: %d", s_Instance->mStatistics.Vertices))
    DEBUG_ONLY(ImGui::Text("Indices: %d", s_Instance->mStatistics.Indices))
    DEBUG_ONLY(ImGui::NewLine())

    // General ---------------------------------------------------------------------------------------------------------
    ImGui::ColorEdit3("Clear Color", &ptr->mClearColor.x);
    if (ImGui::Button("Toggle Wire-frame")) {
      Renderer::ToggleWireframeRendering();
    }

    ImGui::NewLine();

    // Shader ----------------------------------------------------------------------------------------------------------
    ImGui::ColorEdit3("Light Color", &ptr->mLightColor.x);
    ImGui::DragFloat3("Light Position", &ptr->mLightPosition.x, 1.0f);

    // Camera ----------------------------------------------------------------------------------------------------------
    ImGui::DragFloat3("Camera Position", &ptr->camera.GetPosition().x, -1000.0f, 1000.0f);
    ImGui::DragFloat3("Camera Rotation", &ptr->camera.GetRotation().x, -360.0f, 360.0f);
  }
  ImGui::End();
}

/**
 * Called before the Draw() function to allow for per-frame pre-draw functionality such
 * as resetting statistics, clearing buffers etc.
 */
void Renderer::Begin() {
  DEBUG_ONLY(s_Instance->mStatistics.Calls = 0)
  DEBUG_ONLY(s_Instance->mStatistics.Vertices = 0)
  DEBUG_ONLY(s_Instance->mStatistics.Indices = 0)

  Renderer::Access()->camera.Update(1.0);

  glm::vec3 C = s_Instance->mClearColor;
  glClearColor(C.x, C.y, C.z, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * Called after the Draw() function to allow for per-frame post-draw functionality such as
 * swapping the back buffers.
 */
void Renderer::End() {
  glfwSwapBuffers(Window::sWindow);
}

/**
 * Toggles wire-frame rendering mode on or off.
 */
void Renderer::ToggleWireframeRendering() {
  s_Instance->mIsWireframeEnabled = !s_Instance->mIsWireframeEnabled;
  if (s_Instance->mIsWireframeEnabled) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}

