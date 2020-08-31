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
#include "Framework/GL/Shader.h"

#include "./Geometry/Mesh.h"

// TODO: Call OnDestroy for complex items (Texture, Buffers, Mesh etc.)

// TODO: Add Cameras

// TODO: integrate textures into this.
struct RenderingInstance {
  uint32_t MeshID;
  uint32_t TransformID;
  uint32_t MaterialID;
};

enum RenderType {
  SOLID, TRANSPARENT
};

class Repository {

 private:
  static Repository *sInstance;

  // Meshes ------------------------------------------------------------------------------------------------------------
  std::vector<Mesh> mMeshes;
  std::map<std::string, uint32_t> mMeshesMap;

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

  // Shaders ----------------------------------------------------------------------------------------------------------
  std::vector<Shader> mShaders;
  std::map<std::string, uint32_t> mShadersMap;

 public:
  inline static Repository *Get() { return sInstance; };
  bool Init();
  void Destroy();

  // General -----------------------------------------------------------------------------------------------------------
  void ClearAll();
  void ClearInstancesAndTransforms();

  // Meshes ------------------------------------------------------------------------------------------------------------

  uint32_t AddMesh(const Mesh &pMesh);
  Mesh *GetMesh(const std::string &pName);
  uint32_t GetMeshID(const std::string &pName);
  Mesh *GetMesh(uint32_t pID);
  bool MeshExists(const std::string &pName);
  void ClearMeshes();

  // Instances ---------------------------------------------------------------------------------------------------------

  uint32_t AddInstance(int32_t pMeshID, const Transform &pTransform, uint32_t pMaterialID = 0);
  RenderingInstance *GetInstance(uint32_t pID);
  inline const std::vector<RenderingInstance> &GetAllRenderingInstances() const { return mInstances; }

  void ClearInstances();

  // Transforms --------------------------------------------------------------------------------------------------------

  uint32_t AddTransform(const Transform &pTransform = Transform());
  Transform *GetTransform(uint32_t pID);
  Transform *GetTransformForInstance(uint32_t pInstanceID);
  void ClearTransforms();

  // Materials ---------------------------------------------------------------------------------------------------------

  uint32_t AddMaterial(const Material &pMaterial);
  Material *GetMaterial(const std::string &pName);
  uint32_t GetMaterialID(const std::string &pName);
  Material *GetMaterial(uint32_t pID = 0);
  bool MaterialExists(const std::string &pName);
  void ClearMaterials();

  // Textures ----------------------------------------------------------------------------------------------------------

  uint32_t AddTexture(const Texture &pTexture);
  Texture *GetTexture(const std::string &pName);
  uint32_t GetTextureID(const std::string &pName);
  Texture *GetTexture(uint32_t pID = 0);
  bool TextureExists(const std::string &pName);
  void ClearTextures();

  // Shaders ----------------------------------------------------------------------------------------------------------

  uint32_t AddShader(const std::string &pName, const Shader &pShader);
  Shader *GetShader(const std::string &pName);
  uint32_t GetShaderID(const std::string &pName);
  Shader *GetShader(uint32_t pID = 0);
  bool ShaderExists(const std::string &pName);
  void ClearShaders();
};
