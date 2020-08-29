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


#include "RectangleSim.h"
#include "../../Framework/Geometry/Shapes2D.h"

RectangleSim::~RectangleSim() {

}

void RectangleSim::OnInit() {
  // Create the triangle mesh.
  Mesh2 mesh;
  mesh.Create("Rectangle", Rectangle::Vertices(), Rectangle::Indices());
  uint32_t triangle = Repository::Get()->AddMesh(mesh);
  mInstances.push_back(Repository::Get()->AddInstance(triangle, Transform()));
}

void RectangleSim::OnUpdate() {
  Transform *transform = Repository::Get()->GetTransformForInstance(mInstances[0]);
  transform->AddRotate({ 0.0f, 0.0f, 0.1f });
}

void RectangleSim::OnDestroy() {
  Repository::Get()->ClearInstancesAndTransforms();
}

void RectangleSim::OnGUI() {

}
