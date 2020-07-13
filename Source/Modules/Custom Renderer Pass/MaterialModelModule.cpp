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


#include "MaterialModelModule.h"
#include "Math/Random/Random.h"
#include "System/GUI/GUILayer.h"
#include "OpenGL/Renderer.h"

void MaterialModelModule::OnInit(Camera &p_Camera) {
  m_Overrides[0] = true;
  p_Camera.SetAndUpdatePosition({0.0f, 6.0f, 20.0f});

  // Shaders ---------
  m_Shader.AddStage(GL_VERTEX_SHADER, "Resources/Shaders/Model/model.vertex.glsl");
  m_Shader.AddStage(GL_FRAGMENT_SHADER, "Resources/Shaders/Model/model.fragment.glsl");
  m_Shader.Compile();

  m_Model.Load("Resources/Models/dragon.obj");
  m_MultiModel.Load("Resources/Models/tree_low.obj");

//  glEnable(GL_BLEND);
//  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MaterialModelModule::OnUpdate(double dt) {

}

void MaterialModelModule::OnDestroy() {

}

void MaterialModelModule::OnGUI() {
  {
    ImGui::Text("m_Model");
    m_Model.GetMeshMaterial().DisplayWithGUI();

    ImGui::Text("m_MultiModel");
    m_MultiModel.DoMaterialGUI();
  }
}

void MaterialModelModule::OnDraw(Transform &p_Transform, const Camera &p_Camera) {

  Renderer *ptr = Renderer::Access();

  m_Shader.Bind();

  m_Shader.Mat4("u_ViewProjection", p_Camera.GetProjectionView());
  m_Shader.Vec3("u_LightColor", ptr->GetLightColor());
  m_Shader.Vec3("u_LightPosition", ptr->GetLightPosition());
  m_Shader.Vec3("u_CameraPosition", p_Camera.GetPosition());

  // Model
  m_Model.GetMeshMaterial().SubmitAsUniform(m_Shader);
  m_Model.Bind();
  m_Shader.Mat4("u_Model", p_Transform.Transformation());
  CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, m_Model.IndexCount(), GL_UNSIGNED_INT, 0));

  // MultiModel
  Transform mmTF;
  mmTF.SetTranslate({10.0f, 0.0f, 10.0f});
  mmTF.SetScale(glm::vec3(0.5f));
  m_Shader.Mat4("u_Model", mmTF.Transformation());
  m_MultiModel.Render(m_Shader);
}
