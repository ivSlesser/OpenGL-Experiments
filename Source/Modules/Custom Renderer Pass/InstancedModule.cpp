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


#include "InstancedModule.h"
#include "Math/Random/Random.h"
#include "System/GUI/GUILayer.h"
#include "OpenGL/Renderer.h"

void InstancedModule::OnInit(Camera &p_Camera) {
  m_Overrides[0] = true;
  p_Camera.SetAndUpdatePosition({0.0f, 6.0f, 20.0f});

  // Shaders ---------
  m_Shader.AddStage(GL_VERTEX_SHADER, "Resources/Shaders/Model/inst-model.vertex.glsl");
  m_Shader.AddStage(GL_FRAGMENT_SHADER, "Resources/Shaders/Model/inst-model.fragment.glsl");
  m_Shader.Compile();

  // Setup Model VBO's
  std::vector<glm::mat4> modelMatrices;
  srand(glfwGetTime()); // initialize random seed

  float radius = 1000.0;
  float offset = 1000.0f;

  for (unsigned int i = 0; i < m_NumInstances; i++) {
    Transform TF;
    glm::mat4 model = glm::mat4(1.0f);
    // 1. Displace along circle with 'radius' in range [-offset, offset]
    float angle = (float) i / (float) m_NumInstances * 360.0f;
    float displacement = (rand() % (int) (2 * offset * 100)) / 100.0f - offset;
    float x = sin(angle) * radius + displacement;
    displacement = (rand() % (int) (2 * offset * 100)) / 100.0f - offset;
    displacement = (rand() % (int) (2 * offset * 100)) / 100.0f - offset;
    float z = cos(angle) * radius + displacement;
    TF.SetTranslate(glm::vec3(x, 0.0f, z));

    // 2. Scale between 0.05 and 0.25f
    float scale = (rand() % 20) / 100.0f + 0.05;
    TF.SetScale(glm::vec3(scale));

    // 3. Add random rotation around the y axis.
    TF.AddRotate(glm::vec3(0.0f, (rand() % 360), 0.0f));

    // 4. now add to list of matrices
    modelMatrices.push_back(TF.Transformation());
  }

  m_MultiModel.LoadAsInstanced("Resources/Models/tree_low.obj", modelMatrices);
}

void InstancedModule::OnUpdate(double dt) {

}

void InstancedModule::OnDestroy() {

}

void InstancedModule::OnGUI() {
  ImGui::Text("m_MultiModel");
  m_MultiModel.DoMaterialGUI();
}

void InstancedModule::OnDraw(Transform &p_Transform, const Camera &p_Camera) {

  Renderer *ptr = Renderer::Access();

  m_Shader.Bind();

  m_Shader.Mat4("u_ViewProjection", p_Camera.GetProjectionView());
  m_Shader.Vec3("u_LightColor", ptr->GetLightColor());
  m_Shader.Vec3("u_LightPosition", ptr->GetLightPosition());
  m_Shader.Vec3("u_CameraPosition", p_Camera.GetPosition());

  // MultiModel
  m_MultiModel.Render(m_Shader, true, m_NumInstances);
}
