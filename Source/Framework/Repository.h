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

#include "./Components/Transform.h"
#include "./Components/Material.h"
#include "Framework/GL/Texture.h"

// TODO: Add Meshes
// TODO: Add Shaders
// TODO: Add Cameras

struct RenderingInstance {
  uint32_t MeshID;
  uint32_t InstanceID;
};

enum RenderType {
  SOLID, TRANSPARENT
};

class Repository {

 private:

  // Instances ---------------------------------------------------------------------------------------------------------
  std::vector<RenderingInstance> mInstances;

  // Transforms --------------------------------------------------------------------------------------------------------
  std::vector<Transform> mTransforms;

  // Materials ---------------------------------------------------------------------------------------------------------
  std::vector<Material> mMaterials;
  std::map<std::string, uint32_t> mMaterialsMap;

  // Textures ----------------------------------------------------------------------------------------------------------
  std::vector<Texture> mTextures;
  std::map<std::string, uint32_t> mTexturesMap;

 public:
  bool Init();
  void Destroy();

  // Instances ---------------------------------------------------------------------------------------------------------
  uint32_t AddTransform(uint32_t pMeshID, const Transform &pTransform);
  RenderingInstance *GetInstance(uint32_t pID);

  // Transforms --------------------------------------------------------------------------------------------------------
  uint32_t AddTransform(const Transform &pTransform);
  Transform *GetTransform(uint32_t pID);

  // Materials ---------------------------------------------------------------------------------------------------------
  uint32_t AddMaterial(const Material &pMaterial);
  Material *GetMaterial(const std::string &pName);
  uint32_t GetMaterialID(const std::string &pName);
  Material *GetMaterial(uint32_t pID);

  // Textures ----------------------------------------------------------------------------------------------------------
  uint32_t AddTexture(const Texture &pTexture);
  Texture *GetTexture(const std::string &pName);
  uint32_t GetTextureID(const std::string &pName);
  Texture *GetTexture(uint32_t pID);
};
