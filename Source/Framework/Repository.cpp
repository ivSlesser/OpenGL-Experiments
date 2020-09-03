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
#include "System/GUI/GUILayer.h"

Repository *Repository::sInstance = nullptr;

/**
 * Create the repository, adding default components as needed.
 *
 * @return      True if succeeded.
 */
bool Repository::Create() {
  Repository::sInstance = this;

  // Default Shader ----------------------------------------------------------------------------------------------------
  Shader shader;
  shader.AddStage(GL_VERTEX_SHADER, "Resources/Shaders/default.vertex.glsl");
  shader.AddStage(GL_FRAGMENT_SHADER, "Resources/Shaders/default.fragment.glsl");
  if (!shader.Create()) {
    return false;
  }
  AddShader("Default", shader);

  // Default Material --------------------------------------------------------------------------------------------------
  AddMaterial(Material());

  // Default Texture ---------------------------------------------------------------------------------------------------
  Texture defaultTexture;
  defaultTexture.Create((std::string &) "Default");
  AddTexture(defaultTexture);

  return true;
}

/**
 * Destroys the repository and all stored data.
 */
void Repository::Destroy() {
  Repository::sInstance = nullptr;
  ClearAll();
}

/**
 * Displays the repository data and controls.
 */
void Repository::OnGUI() {
  ImGui::Begin("Repository");
  {
    ImGui::Text("Meshes: %d", (int) mMeshes.size());
    ImGui::Text("Instances: %d", (int) mInstances.size());
    ImGui::Text("Transform: %d", (int) mTransforms.size());
    ImGui::Text("Materials: %d", (int) mMaterials.size());
    ImGui::Text("Textures: %d", (int) mTextures.size());
    ImGui::Text("Shaders: %d", (int) mShaders.size());
  }
  ImGui::End();
}

// ---------------------------------------------------------------------------------------------------------------------
// General -------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

/**
 * Calls the clear functions for each type of stored object.
 */
void Repository::ClearAll() {
  ClearMeshes();
  ClearInstances();
  ClearTransforms();
  ClearMaterials();
  ClearTextures();
  ClearShaders();
}

/**
 * Clears the stored instances and transforms.
 */
void Repository::ClearInstancesAndTransforms() {
  ClearInstances();
  ClearTransforms();
}

// ---------------------------------------------------------------------------------------------------------------------
// Meshes --------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

/**
 * Adds a new mesh to the repository, returning its ID.
 * If a mesh with the same name exists it will return the ID of the existing mesh.
 *
 * @param pMesh             Mesh to add.
 * @return                  ID of the added mesh, or the ID of an existing mesh.
 */
uint32_t Repository::AddMesh(const Mesh &pMesh) {
  // Check that the name doesn't already exist.
  if (MeshExists(pMesh.Name)) {
    return GetMeshID(pMesh.Name);
  }

  // Add the mesh to the vector and the map.
  mMeshesMap[pMesh.Name] = mMeshes.size();
  mMeshes.push_back(pMesh);
  return mMeshes.size() - 1;
}

/**
 * Returns a pointer to a stored mesh given it's name.
 *
 * @param pName             Mesh name to fetch.
 * @return                  A Mesh pointer, or nullptr if it doesn't exist.
 */
Mesh *Repository::GetMesh(const std::string &pName) {
  // Check that the name exists.
  if (!MeshExists(pName)) {
    return nullptr;
  }
  return GetMesh(mMeshesMap[pName]);
}

/**
 * Returns the ID of a stored mesh given it's name.
 *
 * @param pName                     Mesh name to fetch.
 * @return                          The ID of the stored mesh.
 * @throws std::invalid_argument    Thrown if a mesh doesn't exist with that name.
 */
uint32_t Repository::GetMeshID(const std::string &pName) {
  // Check that the name exists.
  if (!MeshExists(pName)) {
    throw std::invalid_argument("Mesh does not exist in the repository");
  }
  return mMeshesMap[pName];
}

/**
 * Returns a pointer to a stored mesh, given its ID.
 *
 * @param pID               Mesh ID to fetch.
 * @return                  A Mesh pointer, or nullptr if it doesn't exist.
 */
Mesh *Repository::GetMesh(uint32_t pID) {
  try {
    return &mMeshes[pID];
  } catch (const std::exception &e) {
    return nullptr;
  }
}

/**
 * Checks a mesh is stored in the repository, given its name.
 *
 * @param pName             Mesh name to fetch.
 * @return                  True if the mesh exists in the repository.
 */
bool Repository::MeshExists(const std::string &pName) {
  return mMeshesMap.count(pName) > 0;
}

/**
 * Clears the stored mesh objects, calling their Destroy() prior to clearing.
 */
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

// TODO: Finish documenting

uint32_t Repository::AddInstance(int32_t pMeshID,
                                 const Transform &pTransform,
                                 uint32_t pMaterialID,
                                 uint32_t pShaderID,
                                 uint32_t pTextureID) {
  // TODO: Make this a map. <RenderingType, <Texture, <MeshID, <Material, Transform>>> also add shader?
  RenderingInstance instance;
  instance.MeshID = pMeshID;
  instance.MaterialID = pMaterialID;
  instance.ShaderID = pShaderID;
  instance.TextureID = pTextureID;
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
  mShadersMap[pName] = mShaders.size();
  mShaders.push_back(pShader);
  return mShaders.size() - 1;
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





