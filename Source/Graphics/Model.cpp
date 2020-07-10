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


#include "Model.h"

bool Model::Load(const char *file) {
  std::ifstream in(file, std::ios::in);
  if (!in) {
	std::cout << "Failed to open file: " << file << std::endl;
	return false;
  }

  std::vector<glm::vec3> positions;
  std::vector<unsigned int> indices;
  std::vector<glm::vec3> normals;

  // Populate positions, indices and normals.
  std::string line;
  while (getline(in, line)) {
	if (line.substr(0, 2) == "v ") {
	  std::istringstream s(line.substr(2));

	  glm::vec3 v;
	  s >> v.x;
	  s >> v.y;
	  s >> v.z;

	  positions.push_back(v);
	} else if (line.substr(0, 2) == "f ") {
	  std::istringstream s(line.substr(2));
	  std::string vertex1, vertex2, vertex3;
	  unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

	  s >> vertex1;
	  s >> vertex2;
	  s >> vertex3;

	  sscanf(vertex1.c_str(), "%d/%d/%d", &vertexIndex[0], &uvIndex[0], &normalIndex[0]);
	  sscanf(vertex2.c_str(), "%d/%d/%d", &vertexIndex[1], &uvIndex[1], &normalIndex[1]);
	  sscanf(vertex3.c_str(), "%d/%d/%d", &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

	  indices.push_back(vertexIndex[0] - 1);
	  indices.push_back(vertexIndex[1] - 1);
	  indices.push_back(vertexIndex[2] - 1);
	} else {
	  /* ignoring this line */
	}
  }

  // Calculate normals
  normals.resize(positions.size(), glm::vec3(0.0, 0.0, 0.0));
  for (int i = 0; i < indices.size(); i += 3) {
	unsigned int ia = indices[i];
	unsigned int ib = indices[i + 1];
	unsigned int ic = indices[i + 2];

	glm::vec3 normal = glm::normalize(glm::cross(
		glm::vec3(positions[ib]) - glm::vec3(positions[ia]),
		glm::vec3(positions[ic]) - glm::vec3(positions[ia])));
	normals[ia] = normals[ib] = normals[ic] = normal;
  }

  // Create a random color
  glm::vec4 color;
  color.r = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
  color.g = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
  color.b = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
//  color.r = 1.0f;
//  color.g = 1.0f;
//  color.b = 1.0f;
  color.a = 1.0f;

  // Create vertices
  std::vector<Vertex> vertices;

  for (int i = 0; i < positions.size(); ++i) {
	vertices.push_back({
	  positions[i], color, glm::vec2(0.0f), normals[i]
	});
  }


  // Create vertex buffer
  vertex_count = vertices.size();
  VAO.Bind();
  VBO.Init(vertices);
  VAO.SetLayout();

  // Create indices

  // Create index buffer
  index_count = indices.size();
  IBO.Init(indices);

  return true;
}
