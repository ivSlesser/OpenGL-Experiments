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

bool Repository::Init() {
  return true;
}

void Repository::Destroy() {

  mInstances.clear();

  mTransforms.clear();

  mMaterials.clear();
  mMaterialsMap.clear();

  mTextures.clear();
  mTexturesMap.clear();
}

// ---------------------------------------------------------------------------------------------------------------------
// Instances -----------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

uint32_t Repository::AddTransform(uint32_t pMeshID, const Transform &pTransform) {
  // TODO: Make this a map. <RenderingType, <MeshID, <Material, Transform>>
  RenderingInstance instance;
  instance.MeshID = pMeshID;
  instance.InstanceID = AddTransform(pTransform);
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

// ---------------------------------------------------------------------------------------------------------------------
// Materials -----------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

uint32_t Repository::AddMaterial(const Material &pMaterial) {
  // Check that the name doesn't already exist.
  if (mMaterialsMap.count(pMaterial.Name) > 0) {
    // It already exists, we won't allow duplicates.
    throw std::invalid_argument("Material already exists in the repository");
  }

  // Add the material to the vector and the map.
  mMaterialsMap[pMaterial.Name] = mMaterials.size();
  mMaterials.push_back(pMaterial);
  return mMaterials.size() - 1;
}

Material *Repository::GetMaterial(const std::string &pName) {
  // Check that the name exists.
  if (mMaterialsMap.count(pName) == 0) {
    throw std::invalid_argument("Material does not exist in the repository");
  }
  return GetMaterial(mMaterialsMap[pName]);
}

uint32_t Repository::GetMaterialID(const std::string &pName) {
  // Check that the name exists.
  if (mMaterialsMap.count(pName) == 0) {
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

// ---------------------------------------------------------------------------------------------------------------------
// Textures ------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

uint32_t Repository::AddTexture(const Texture &pTexture) {
  // Check that the name doesn't already exist.
  if (mTexturesMap.count(pTexture.Name()) > 0) {
    // It already exists, we won't allow duplicates.
    throw std::invalid_argument("Texture already exists in the repository");
  }

  // Add the material to the vector and the map.
  mTexturesMap[pTexture.Name()] = mTextures.size();
  mTextures.push_back(pTexture);
  return mTextures.size() - 1;
}

Texture *Repository::GetTexture(const std::string &pName) {
  // Check that the name exists.
  if (mTexturesMap.count(pName) == 0) {
    throw std::invalid_argument("Texture does not exist in the repository");
  }

  return GetTexture(mTexturesMap[pName]);
}

uint32_t Repository::GetTextureID(const std::string &pName) {
  // Check that the name exists.
  if (mTexturesMap.count(pName) == 0) {
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


