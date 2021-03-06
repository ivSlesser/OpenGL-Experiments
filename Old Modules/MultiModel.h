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


#pragma once

#include "Common.h"
#include "Mesh.h"
#include "Framework/Components/Material.h"
#include "Framework/GL/Shader.h"

struct MultiModelLoadResult {
  std::string Name;
  std::vector<Vertex> Vertices;
  std::vector<unsigned int> Indices;
};

class MultiModel {

 private:
  std::vector<Mesh *> m_Meshes;
  std::vector<Material *> m_Materials;
  bool m_Instanced = false;

 public:
  MultiModel() {}
  virtual ~MultiModel();

  bool Load(const char *file);
  bool LoadAsInstanced(const char *file, const std::vector<glm::mat4> &pMatrices);

  void Render(Shader &pShader);
  void Render(Shader &pShader, bool pInstanced, unsigned int pInstanceCount);

  void DoMaterialGUI() {
    for (Material *m : m_Materials) {
      m->DisplayWithGUI();
    }
  }

 private:
  void Clear();
  std::vector<MultiModelLoadResult> DoLoad(const char *file);
};
