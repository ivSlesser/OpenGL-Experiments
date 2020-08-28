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


#include "MultiModel.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "Externals/tiny_obj_loader.h"
#include "Framework/Renderer.h"
#include "Framework/GL/DrawHandler.h"

MultiModel::~MultiModel() {
  Clear();
}

void MultiModel::Clear() {
  for (Mesh *mesh : m_Meshes) {
    delete mesh;
  }

  for (Material *material : m_Materials) {
    delete material;
  }
}

bool MultiModel::Load(const char *file) {

  Clear();
  m_Instanced = false;

  std::vector<MultiModelLoadResult> data = DoLoad(file);

  if (data.size() == 0) {
    return false;
  }

  for (MultiModelLoadResult result : data) {
    Mesh *mesh = new Mesh();
    mesh->Name = result.Name;
    mesh->Load(result.Vertices, result.Indices);
    m_Meshes.push_back(mesh);
  }

  return true;
}

void MultiModel::Render(Shader &pShader) {
  Render(pShader, false, 1);
}

void MultiModel::Render(Shader &pShader, bool pInstanced, unsigned int pInstanceCount) {

  // Bind Materials
  unsigned int i = 0;
  for (Material *m : m_Materials) {
    m->SubmitAsUniform(pShader, i++);
  }

  for (Mesh *m : m_Meshes) {
    m->Bind();
    if (pInstanced) {
      DrawHandler::IndexedInstance(m->IndexCount, pInstanceCount);
    } else {
      DrawHandler::Indexed(m->IndexCount);
    }
  }
}

bool MultiModel::LoadAsInstanced(const char *file, const std::vector<glm::mat4> &pMatrices) {
  Clear();
  m_Instanced = true;

  std::vector<MultiModelLoadResult> data = DoLoad(file);

  if (data.size() == 0) {
    return false;
  }

  for (MultiModelLoadResult result : data) {
    Mesh *mesh = new Mesh();
    mesh->Name = result.Name;
    mesh->LoadInstanced(result.Vertices, result.Indices, pMatrices);
    m_Meshes.push_back(mesh);
  }

  return true;
}

std::vector<MultiModelLoadResult> MultiModel::DoLoad(const char *file) {

  std::vector<MultiModelLoadResult> result;

  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;

  std::string warn;
  std::string err;

  if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, file, "Resources/Models/")) {
    return result;
  }

  if (!warn.empty()) {
    std::cout << warn << std::endl;
  }

  if (!err.empty()) {
    std::cerr << err << std::endl;
    return result;
  }

  // First Create Materials
  for (int m = 0; m < materials.size(); ++m) {

    Material *material = new Material();
    auto mat = materials[m];
    material->Name = mat.name;
    material->Ambient = glm::vec3(mat.ambient[0], mat.ambient[1], mat.ambient[2]);
    material->Diffuse = glm::vec3(mat.diffuse[0], mat.diffuse[1], mat.diffuse[2]);
    material->Specular = glm::vec3(mat.specular[0], mat.specular[1], mat.specular[2]);
    material->Shine = mat.shininess;
    material->Dissolve = mat.dissolve;
    m_Materials.push_back(material);
  }

  // Then the meshes
  for (size_t s = 0; s < shapes.size(); s++) {

    result.push_back(MultiModelLoadResult());

    // Loop over faces
    size_t index_offset = 0;

    unsigned int I = 0;

    for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
      int fv = shapes[s].mesh.num_face_vertices[f];
      int fm = shapes[s].mesh.material_ids[f];

      // Loop over vertices in the face.
      for (size_t v = 0; v < fv; v++) {

        tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

        Vertex vertex;
        vertex.position = glm::vec3(attrib.vertices[3 * idx.vertex_index + 0],
                                    attrib.vertices[3 * idx.vertex_index + 1],
                                    attrib.vertices[3 * idx.vertex_index + 2]);
        vertex.color = glm::vec4(attrib.colors[3 * idx.vertex_index + 0],
                                 attrib.colors[3 * idx.vertex_index + 1],
                                 attrib.colors[3 * idx.vertex_index + 2],
                                 1.0f);
        vertex.normals = glm::vec3(attrib.normals[3 * idx.normal_index + 0],
                                   attrib.normals[3 * idx.normal_index + 1],
                                   attrib.normals[3 * idx.normal_index + 2]);
        vertex.tex_coordinates =
            glm::vec2(attrib.texcoords[2 * idx.texcoord_index + 0], attrib.texcoords[2 * idx.texcoord_index + 1]);
        vertex.mat_index = fm;
        result[s].Vertices.push_back(vertex);
        result[s].Indices.push_back(I++);
      }

      index_offset += fv;
    }

    result[s].Name = shapes[s].name;
  }

  return result;
}



