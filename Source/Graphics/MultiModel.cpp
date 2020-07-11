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

MultiModel::~MultiModel() {
  for (Mesh *mesh : m_Meshes) {
	delete mesh;
  }
}

bool MultiModel::Load(const char *file) {

  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;

  std::string warn;
  std::string err;

  if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, file, "Resources/Models/")) {
	return false;
  }

  if (!warn.empty()) {
	std::cout << warn << std::endl;
  }

  if (!err.empty()) {
	std::cerr << err << std::endl;
	return false;
  }

  // Loop over shapes
  for (size_t s = 0; s < shapes.size(); s++) {

	Mesh *mesh = new Mesh();

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	// Loop over faces
	size_t index_offset = 0;

	for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {

	  int fv = shapes[s].mesh.num_face_vertices[f];
	  int fm = shapes[s].mesh.material_ids[f];

	  // Loop over vertices in the face.
	  for (size_t v = 0; v < fv; v++) {

		tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
		indices.push_back(3 * idx.vertex_index);

		Vertex vertex;
		vertex.position = glm::vec3(attrib.vertices[3 * idx.vertex_index + 0],
									attrib.vertices[3 * idx.vertex_index + 1],
									attrib.vertices[3 * idx.vertex_index + 2]);
		vertex.color = glm::vec4(attrib.colors[3 * idx.vertex_index + 0],
								 attrib.colors[3 * idx.vertex_index + 1],
								 attrib.colors[3 * idx.vertex_index + 2],
								 1.0f)
		vertex.normals = glm::vec3(attrib.normals[3 * idx.normal_index + 0],
								   attrib.normals[3 * idx.normal_index + 1],
								   attrib.normals[3 * idx.normal_index + 2]);
		vertex.tex_coordinates =
			glm::vec2(attrib.texcoords[2 * idx.texcoord_index + 0], attrib.texcoords[2 * idx.texcoord_index + 1]);
		vertex.mat_index = fm;
		vertices.push_back(vertex);

		mesh->UsesMaterials = fm != -1;
	  }

	  index_offset += fv;
	}

	mesh->Load(vertices, indices);
	mesh->Name = shapes[s].name;
	m_Meshes.push_back(mesh);

  }

  for (int m = 0; m < materials.size(); ++m) {

	Material material;
	auto mat = materials[m];
	material.Name = mat.name;
	material.Ambient = glm::vec3(mat.ambient[0], mat.ambient[1], mat.ambient[2]);
	material.Diffuse = glm::vec3(mat.diffuse[0], mat.diffuse[1], mat.diffuse[2]);
	material.Specular = glm::vec3(mat.specular[0], mat.specular[1], mat.specular[2]);
	material.Shine = mat.shininess;
	material.Dissolve = mat.dissolve;
	m_Materials.push_back(material);
  }

  return true;
}

