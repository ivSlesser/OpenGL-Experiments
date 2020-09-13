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

#include "Application.h"
#include "System/Clock.h"
#include "System/GUI/GUILayer.h"
#include "Repository.h"
#include "./Geometry/Shapes2D.h"
#include "Framework/GL/BufferUtils.h"

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

Renderer::Renderer() {
  s_Instance = this;
}

/**
 * Constructor, handles creation of the renderer
 */
void Renderer::Create() {

  // Uniform Buffers ---------------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------------------------------
  mUniformBuffers.GeneralUBO.Create("General", {sizeof(GeneralUniformBuffer), GeneralUniformBuffer()});
  mUniformBuffers.CameraUBO.Create("Camera", {sizeof(CameraUniformBuffer), CameraUniformBuffer()});

  // Default Shader ----------------------------------------------------------------------------------------------------
  Shader shader;
  shader.AddStage(GL_VERTEX_SHADER, "Resources/Shaders/default.vertex.glsl");
  shader.AddStage(GL_FRAGMENT_SHADER, "Resources/Shaders/default.fragment.glsl");
  shader.Create();
  Renderer::RegisterUniformBuffersToShader(shader.ID());
  Repository::Get()->AddShader("Default", shader);


  // Post Processing Set-Up --------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------------------------------

  // Post Processing Shader
  Shader ppShader;
  ppShader.AddStage(GL_VERTEX_SHADER, "Resources/Shaders/PostProcessing/pp.vertex.glsl");
  ppShader.AddStage(GL_FRAGMENT_SHADER, "Resources/Shaders/PostProcessing/pp.fragment.glsl");
  ppShader.Create();
  Renderer::RegisterUniformBuffersToShader(ppShader.ID());
  mPostProcessingShaderID = Repository::Get()->AddShader("Post-Processing", ppShader);
  mPostActionShaderID = mPostProcessingShaderID;

  // Depth Processing Shader
  Shader dShader;
  dShader.AddStage(GL_VERTEX_SHADER, "Resources/Shaders/PostProcessing/pp.vertex.glsl");
  dShader.AddStage(GL_FRAGMENT_SHADER, "Resources/Shaders/PostProcessing/pp.fragment.glsl");
  dShader.Create();
  Renderer::RegisterUniformBuffersToShader(dShader.ID());
  mDepthShaderID = Repository::Get()->AddShader("Depth Post Processing", dShader);

  // Display rectangle
  mScreenVAO.Bind();
  mScreenVBO.Create(Rectangle::Vertices());
  mScreenVAO.SetLayout();
  mScreenIBO.Create(Rectangle::Indices());

  auto dims = Window::GetDimensions();
  int width, height;

#ifdef __APPLE__
  width = dims.x * 2;
  height = dims.y * 2;
#endif
  if (!mPrimaryFBO.Create(width, height)) {
    std::abort();
  }
  Window::ToggleFramebufferUsage(true); // TODO: Needed?
}

/**
 * Performs rendering functions, setting shader variables and querying the repository for rendering instances.
 * Will load the values defined in each instance before rendering the actual geometry.
 */
void Renderer::Draw() {

  Renderer *ptr = Renderer::Access();
  auto windowXY = Window::GetDimensions();

  ptr->mPrimaryFBO.Bind(windowXY);

  // Render Scene To FBO -----------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------------------------------

  const std::vector<RenderingInstance> &instances = Repository::Get()->GetAllRenderingInstances();

  for (const RenderingInstance &instance : instances) {

    // TODO: Shader will be a map!
    Shader *shader = Repository::Get()->GetShader(instance.ShaderID); // Default Shader
    shader->Bind();

    shader->Vec3("u_CameraPosition", ptr->camera.GetPosition());
    shader->Bool("u_ApplyFog", ptr->mSettings.ApplyFog);
    shader->Float("u_Density", ptr->mSettings.FogDensity);
    shader->Float("u_Gradient", ptr->mSettings.FogGradient);

    // Get Components
    Mesh *mesh = Repository::Get()->GetMesh(instance.MeshID);
    Transform *transform = Repository::Get()->GetTransform(instance.TransformID);
    Material *material = Repository::Get()->GetMaterial(instance.MaterialID);
    Texture *texture = Repository::Get()->GetTexture(instance.TextureID); // TODO: Also need to check for alpha.

    // Bind Texture
    texture->Bind();

    // Upload Model Matrix
    shader->Mat4("u_Model", transform->Transformation());

    // Upload Material
    material->SubmitAsUniform(shader);

    // Simulation Draw Setup
    Application::GetSimulation()->OnDraw(shader);

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

  // Apply PP & Output FBO ---------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------------------------------
  bool wfState = ptr->mSettings.IsWireframeEnabled; // Store mWireFrameRendering state
  if (wfState) { // Toggle wire-frame off so it won't disturb the output rectangle.
    Renderer::SetWireframeRendering(false);
  }

  ptr->mPrimaryFBO.Bind(0, windowXY);
  ptr->mPrimaryFBO.BindColorAttachment();

  Shader *ppShader = Repository::Get()->GetShader(ptr->mPostActionShaderID); // Default Shader
  ppShader->Bind();

  ppShader->Bool("u_Greyscale", ptr->mPPSettings.ApplyGreyscale);
  ppShader->Bool("u_Invert", ptr->mPPSettings.ApplyInvert);
  ppShader->Float("u_ContrastStrength", ptr->mPPSettings.ContrastStrength);

  ptr->mScreenVAO.Bind();
  ptr->mScreenIBO.Bind();
  CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, Rectangle::IndexCount(), GL_UNSIGNED_INT, 0));

  if (wfState) { // Toggle wire-frame back on.
    Renderer::SetWireframeRendering(true);
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
    ImGui::Text("General");
    ImGui::ColorEdit3("Clear Color", &ptr->mLightSettings.SkyColor.x);
    if (ImGui::Button("Toggle Wire-frame")) {
      Renderer::ToggleWireframeRendering();
    }

    ImGui::NewLine();

    // Shader ----------------------------------------------------------------------------------------------------------
    ImGui::Text("Lighting");
    ImGui::ColorEdit3("Sun Color", &ptr->mLightSettings.SunColor.x);
    ImGui::DragFloat3("Sun Position", &ptr->mLightSettings.SunPosition.x, 1.0f);
    ImGui::DragFloat("Ambient Strength", &ptr->mLightSettings.AmbientStrength, 0.01f, 0.0f, 1.0f);
    ImGui::DragFloat("Specular Strength", &ptr->mLightSettings.SpecularStrength, 0.01f, 0.0f, 1.0f);
    ImGui::NewLine();

    // Camera ----------------------------------------------------------------------------------------------------------
    ImGui::Text("Camera");
    ImGui::DragFloat3("Camera Position", &ptr->camera.GetPosition().x, -1000.0f, 1000.0f);
    ImGui::DragFloat3("Camera Rotation", &ptr->camera.GetRotation().x, -360.0f, 360.0f);
    ImGui::NewLine();

    // Post Processing -------------------------------------------------------------------------------------------------
    ImGui::Text("Post Processing");
    ImGui::Checkbox("Use Greyscale?", &ptr->mPPSettings.ApplyGreyscale);
    ImGui::Checkbox("Use Inverse?", &ptr->mPPSettings.ApplyInvert);
    ImGui::DragFloat("Contrast", &ptr->mPPSettings.ContrastStrength, 0.01f);
    ImGui::NewLine();

    // Fog -------------------------------------------------------------------------------------------------------------
    ImGui::Text("Fog");
    ImGui::Checkbox("Apply Fog?", &ptr->mSettings.ApplyFog);
    ImGui::DragFloat("Density", &ptr->mSettings.FogDensity, 0.001f, 0.0f, 1.0f);
    ImGui::DragFloat("Gradient", &ptr->mSettings.FogGradient, 0.01f, 0.0f, 4.0f);
    ImGui::NewLine();
  }
  ImGui::End();
}

/**
 * Called before the Draw() function to allow for per-frame pre-draw functionality such
 * as resetting statistics, clearing buffers etc.
 */
void Renderer::Begin() {

  auto ptr = Renderer::Access();

  DEBUG_ONLY(s_Instance->mStatistics.Calls = 0)
  DEBUG_ONLY(s_Instance->mStatistics.Vertices = 0)
  DEBUG_ONLY(s_Instance->mStatistics.Indices = 0)

  ptr->camera.Update(1.0);

  glm::vec3 C = s_Instance->mLightSettings.SkyColor;
  glClearColor(C.x, C.y, C.z, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Setup Uniform Buffer ----------------------------------------------------------------------------------------------
  // -------------------------------------------------------------------------------------------------------------------

  // General UBO ------------------------------
  ptr->mUniformBuffers.GeneralUBO.Bind();
  GeneralUniformBuffer *mPtr = BufferUtils::MapBuffer<GeneralUniformBuffer>(GL_UNIFORM_BUFFER, GL_READ_WRITE);
  mPtr->SkyColor = ptr->mLightSettings.SkyColor;
  mPtr->AmbientStrength = ptr->mLightSettings.AmbientStrength;
  mPtr->SunColor = ptr->mLightSettings.SunColor;
  mPtr->SpecularStrength = ptr->mLightSettings.SpecularStrength;
  mPtr->SunPosition = ptr->mLightSettings.SunPosition;
  mPtr->Time = Clock::ElapsedTime;
  mPtr->DeltaTime = Clock::DeltaTime;
  BufferUtils::UnmapBuffer(GL_UNIFORM_BUFFER);

  // Camera UBO -------------------------------
  ptr->mUniformBuffers.CameraUBO.Bind();
  CameraUniformBuffer *cPtr = BufferUtils::MapBuffer<CameraUniformBuffer>(GL_UNIFORM_BUFFER, GL_READ_WRITE);
  cPtr->View = ptr->camera.GetView();
  cPtr->Projection = ptr->camera.GetProjection();
  cPtr->ViewProjection = ptr->camera.GetProjectionView();
  cPtr->Position = ptr->camera.GetPosition();
  cPtr->Near = ptr->camera.Near();
  cPtr->Front = ptr->camera.GetFront();
  cPtr->Far = ptr->camera.Far();
  cPtr->Up = ptr->camera.GetUp();
  BufferUtils::UnmapBuffer(GL_UNIFORM_BUFFER);
}

/**
 * Called after the Draw() function to allow for per-frame post-draw functionality such as
 * swapping the back buffers.
 */
void Renderer::End() {
  glfwSwapBuffers(Window::sWindow);
}

// TODO: Doc
void Renderer::RegisterUniformBuffersToShader(uint32_t pShaderID) {
  s_Instance->mUniformBuffers.GeneralUBO.PerShaderBinding(pShaderID);
  s_Instance->mUniformBuffers.CameraUBO.PerShaderBinding(pShaderID);
}

/**
 * Toggles wire-frame rendering mode on or off.
 */
void Renderer::ToggleWireframeRendering() {
  Renderer::SetWireframeRendering(!s_Instance->mSettings.IsWireframeEnabled);
}

/**
 * Set the wire-frame rendering mode to the specified value.
 *
 * @param pTo       Boolean value to set to.
 */
void Renderer::SetWireframeRendering(bool pTo) {
  s_Instance->mSettings.IsWireframeEnabled = pTo;
  if (s_Instance->mSettings.IsWireframeEnabled) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}


