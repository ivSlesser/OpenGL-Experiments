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


#include "SimpleGeometrySim.h"
#include "../../Framework/Geometry/Shapes2D.h"
#include "../../Framework/Geometry/Shapes3D.h"
#include "Externals/ImGUI.hpp"


void SimpleGeometrySim::OnInit() {
  SetSelection(mSelection);
}

void SimpleGeometrySim::OnUpdate() {
  Transform *transform = Repository::Get()->GetTransformForInstance(mInstances[0]);
//  transform->AddRotate({ 0.0f, 0.0f, 0.1f });
}

void SimpleGeometrySim::OnDestroy() {
  Repository::Get()->ClearInstancesAndTransforms();
}

void SimpleGeometrySim::SetSelection(Selection pSelection) {
  mInstances.clear();
  Repository::Get()->ClearInstancesAndTransforms();

  mSelection = pSelection;

  switch (mSelection) {
    case Selection::TRIANGLE:
      CreateTriangle();
      break;
    case Selection::RECTANGLE:
      CreateRectangle();
      break;
    case Selection::CUBE:
      CreateCube();
      break;
  }
}

void SimpleGeometrySim::OnGUI() {

  // Selection ---------------------------------------------------------------------------------------------------------
  {
    ImGui::Text("Select Geometry");

    if (ImGui::Button("Triangle")) {
      SetSelection(Selection::TRIANGLE);
      return;
    }

    if (ImGui::Button("Rectangle")) {
      SetSelection(Selection::RECTANGLE);
      return;
    }

    if (ImGui::Button("Cube")) {
      SetSelection(Selection::CUBE);
      return;
    }
  }

  // Transform ---------------------------------------------------------------------------------------------------------
  {
    ImGui::Text("Transform");
    Transform *transform = Repository::Get()->GetTransformForInstance(mInstances[0]);

    glm::vec3 translate = transform->GetTranslate();
    if (ImGui::DragFloat3("Position", &translate.x, 0.1f)) {
      transform->SetTranslate(translate);
    }

    glm::vec3 scale = transform->GetScale();
    if (ImGui::DragFloat3("Scale", &scale.x, 0.1f, 0.0f)) {
      if (scale.x < 0.0f) scale.x = 0.0f;
      if (scale.y < 0.0f) scale.z = 0.0f;
      if (scale.y < 0.0f) scale.z = 0.0f;
      transform->SetScale(scale);
    }

    float scalexyz = transform->GetScale().x;
    if (ImGui::DragFloat("Scale (XYZ)", &scalexyz, 0.1f, 1.0f, 10.0f)) {
      transform->SetScale(glm::vec3(scalexyz));
    }

    glm::vec3 rotation = transform->GetRotate();
    if (ImGui::DragFloat3("Rotation", &rotation.x, 0.1f, -360.0f, 360.0f)) {
      transform->SetRotate(rotation);
    }
  }

  // Material ----------------------------------------------------------------------------------------------------------
  {
    ImGui::Text("Material");
    Material *material = Repository::Get()->GetMaterial(mInstances[0]);
    material->DisplayWithGUI(0);
  }

}

void SimpleGeometrySim::CreateTriangle() {
  Mesh2 triangleMesh;
  triangleMesh.Create("Triangle", Triangle::Vertices(), Triangle::Indices());
  uint32_t triangle = Repository::Get()->AddMesh(triangleMesh);
  mInstances.push_back(Repository::Get()->AddInstance(triangle, Transform()));
}

void SimpleGeometrySim::CreateRectangle() {
  Mesh2 rectangleMesh;
  rectangleMesh.Create("Rectangle", Rectangle::Vertices(), Rectangle::Indices());
  uint32_t rectangle = Repository::Get()->AddMesh(rectangleMesh);
  mInstances.push_back(Repository::Get()->AddInstance(rectangle, Transform()));
}

void SimpleGeometrySim::CreateCube() {
  Mesh2 cubeMesh;
  cubeMesh.Create("Cube", Cube::Vertices(), Cube::Indices());
  uint32_t rectangle = Repository::Get()->AddMesh(cubeMesh);
  mInstances.push_back(Repository::Get()->AddInstance(rectangle, Transform()));
}

