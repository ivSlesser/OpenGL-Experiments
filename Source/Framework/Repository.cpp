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

#include "Repository.h"

Repository *Repository::sInstance = nullptr;

bool Repository::Init() {
  Repository::sInstance = this;

  AddMaterial(Material()); // Default material.

  return true;
}

void Repository::Destroy() {
  Repository::sInstance = nullptr;
  ClearAll();
}

// ---------------------------------------------------------------------------------------------------------------------
// General -------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

void Repository::ClearAll() {
  ClearMeshes();
  ClearInstances();
  ClearTransforms();
  ClearMaterials();
  ClearTextures();
  ClearShaders();
}

void Repository::ClearInstancesAndTransforms() {
  ClearInstances();
  ClearTransforms();
}

// ---------------------------------------------------------------------------------------------------------------------
// Meshes --------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

uint32_t Repository::AddMesh(const Mesh &pMesh) {
  // Check that the name doesn't already exist.
  if (MeshExists(pMesh.Name)) {
    return GetMeshID(pMesh.Name);
  }

  // Add the material to the vector and the map.
  mMeshesMap[pMesh.Name] = mMeshes.size();
  mMeshes.push_back(pMesh);
  return mMeshes.size() - 1;
}

Mesh *Repository::GetMesh(const std::string &pName) {
  // Check that the name exists.
  if (!MeshExists(pName)) {
    return nullptr;
  }
  return GetMesh(mMeshesMap[pName]);
}

uint32_t Repository::GetMeshID(const std::string &pName) {
  // Check that the name exists.
  if (!MeshExists(pName)) {
    throw std::invalid_argument("Mesh does not exist in the repository");
  }
  return mMeshesMap[pName];
}

Mesh *Repository::GetMesh(uint32_t pID) {
  try {
    return &mMeshes[pID];
  } catch (const std::exception &e) {
    return nullptr;
  }
}

bool Repository::MeshExists(const std::string &pName) {
  return mMeshesMap.count(pName) > 0;
}

void Repository::ClearMeshes() {

  for (Mesh &mesh : mMeshes) {
    mesh.Destroy();
  }

  mMeshes.clear();
  mMeshesMap.clear();
}

// ---------------------------------------------------------------------------------------------------------------------
// Instances -----------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

uint32_t Repository::AddInstance(int32_t pMeshID, const Transform &pTransform, uint32_t pMaterialID) {
  // TODO: Make this a map. <RenderingType, <MeshID, <Material, Transform>>
  RenderingInstance instance;
  instance.MeshID = pMeshID;
  instance.MaterialID = pMaterialID;
  instance.TransformID = AddTransform(pTransform);
  mInstances.push_back(instance);
  return mInstances.size() - 1;
}

RenderingInstance *Repository::GetInstance(uint32_t pID) {
  try {
    return &mInstances[pID];
  } catch (const std::exception &e) {
    return nullptr;
  }
}

void Repository::ClearInstances() {
  mInstances.clear();
}

// ---------------------------------------------------------------------------------------------------------------------
// Transforms ----------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

uint32_t Repository::AddTransform(const Transform &pTransform) {
  mTransforms.push_back(pTransform);
  return mTransforms.size() - 1;
}

Transform *Repository::GetTransform(uint32_t pID) {
  try {
    return &mTransforms[pID];
  } catch (const std::exception &e) {
    return nullptr;
  }
}

Transform *Repository::GetTransformForInstance(uint32_t pInstanceID) {
  try {
    return GetTransform(GetInstance(pInstanceID)->TransformID);
  } catch (const std::exception &e) {
    return nullptr;
  }
}

void Repository::ClearTransforms() {
  mTransforms.clear();
}

// ---------------------------------------------------------------------------------------------------------------------
// Materials -----------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

uint32_t Repository::AddMaterial(const Material &pMaterial) {
  // Check that the name doesn't already exist.
  if (MaterialExists(pMaterial.Name)) {
    return GetMaterialID(pMaterial.Name);
  }

  // Add the material to the vector and the map.
  mMaterialsMap[pMaterial.Name] = mMaterials.size();
  mMaterials.push_back(pMaterial);
  return mMaterials.size() - 1;
}

Material *Repository::GetMaterial(const std::string &pName) {
  // Check that the name exists.
  if (!MaterialExists(pName)) {
    return nullptr;
  }
  return GetMaterial(mMaterialsMap[pName]);
}

uint32_t Repository::GetMaterialID(const std::string &pName) {
  // Check that the name exists.
  if (!MaterialExists(pName)) {
    throw std::invalid_argument("Material does not exist in the repository");
  }
  return mMaterialsMap[pName];
}

Material *Repository::GetMaterial(uint32_t pID) {
  try {
    return &mMaterials[pID];
  } catch (const std::exception &e) {
    return nullptr;
  }
}

bool Repository::MaterialExists(const std::string &pName) {
  return mMaterialsMap.count(pName) > 0;
}

void Repository::ClearMaterials() {
  mMaterials.clear();
  mMaterialsMap.clear();
}

// ---------------------------------------------------------------------------------------------------------------------
// Textures ------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

uint32_t Repository::AddTexture(const Texture &pTexture) {
  // Check that the name doesn't already exist.
  if (TextureExists(pTexture.Name())) {
    // It already exists, we won't allow duplicates.
    return GetTextureID(pTexture.Name());
  }

  // Add the material to the vector and the map.
  mTexturesMap[pTexture.Name()] = mTextures.size();
  mTextures.push_back(pTexture);
  return mTextures.size() - 1;
}

Texture *Repository::GetTexture(const std::string &pName) {
  // Check that the name exists.
  if (!TextureExists(pName)) {
    return nullptr;
  }
  return GetTexture(mTexturesMap[pName]);
}

uint32_t Repository::GetTextureID(const std::string &pName) {
  // Check that the name exists.
  if (!TextureExists(pName)) {
    throw std::invalid_argument("Texture does not exist in the repository");
  }
  return mTexturesMap[pName];
}

Texture *Repository::GetTexture(uint32_t pID) {
  try {
    return &mTextures[pID];
  } catch (const std::exception &e) {
    return nullptr;
  }
}

bool Repository::TextureExists(const std::string &pName) {
  return mTexturesMap.count(pName) > 0;
}

void Repository::ClearTextures() {
  mTextures.clear();
  mTexturesMap.clear();
}

// ---------------------------------------------------------------------------------------------------------------------
// Shaders -------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

uint32_t Repository::AddShader(const std::string &pName, const Shader &pShader) {
  if (ShaderExists(pName)) {
    return GetShaderID(pName);
  }
  // Add the material to the vector and the map.
  mTexturesMap[pName] = mShaders.size();
  mShaders.push_back(pShader);
  return mTextures.size() - 1;
}

Shader *Repository::GetShader(const std::string &pName) {
  if (!ShaderExists(pName)) {
    return nullptr;
  }
  return GetShader(mShadersMap[pName]);
}

uint32_t Repository::GetShaderID(const std::string &pName) {
  if (!ShaderExists(pName)) {
    throw std::invalid_argument("Shader does not exist in the repository");
  }
  return mShadersMap[pName];
}

Shader *Repository::GetShader(uint32_t pID) {
  try {
    return &mShaders[pID];
  } catch (const std::exception &e) {
    return nullptr;
  }
}

bool Repository::ShaderExists(const std::string &pName) {
  return mShadersMap.count(pName) > 0;
}

void Repository::ClearShaders() {
  mShaders.clear();
  mShadersMap.clear();
}




