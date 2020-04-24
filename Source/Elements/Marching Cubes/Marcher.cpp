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


#include "Marcher.h"
#include "Elements/Marching Cubes/Tables.h"

Marcher::Marcher(const glm::vec2 &pDimensions)
    : m_Dimensions(pDimensions) {
}

void Marcher::March(float pThreshold) {

  m_Threshold = pThreshold;

  m_Data.clear();
  m_Vertices.clear();
  m_Indices.clear();

  // Generate the data
  double zoff = 0.0;
  for (int z = 0; z < m_Dimensions.x + 1; ++z) {
    for (int x = 0; x < m_Dimensions.x + 1; ++x) {
      for (int y = 0; y < m_Dimensions.y + 1; ++y) {
        float height = 3.0f * (float) m_Perlin.Noise(
            2, 0.6,
            x / 16.0 * 0.1 + 0.001,
            y / 16.0 * 0.1 + 0.001,
            z / 16.0 * 0.1 + 0.001);
          m_Data.push_back(y - height);
      }
    }
  }

  // Loop through each segment in our chunk.
  for (int x = 0; x < m_Dimensions.x; ++x) {
    for (int y = 0; y < m_Dimensions.y; ++y) {
      for (int z = 0; z < m_Dimensions.x; ++z) {

        // Create an array of floats representing each corner of a cube and get the value from our data grid.
        float cube[8];

        for (int i = 0; i < 8; i++) {
          glm::vec3 corner = glm::vec3(x, y, z) + Tables::Corners[i];
          cube[i] = m_Data[I3D(corner.x, corner.y, corner.z)];
        }

        // Pass the cube into a function which performs in the in-cell operation.
        CellOperation(cube, glm::vec3(x, y, z));
      }
    }
  }
}

void Marcher::CellOperation(float *pCube, const glm::vec3 &pPosition) {

  // Get the configuration index of this cube.
  int configIndex = GetCubeConfiguration(pCube);

  // If the configuration of this cube is 0 or 255 (completely inside the terrain or completely outside of it) we don't need to do anything.
  if (configIndex == 0 || configIndex == 255)
    return;

  // Loop through the triangles. There are never more than 5 triangles to a cube and only three vertices to a triangle.
  int edgeIndex = 0;
  for (int i = 0; i < 5; i++) {

    // TRIANGLE
    int triangle[3];
    for (int p = 0; p < 3; p++) {
      // Get the current indice. We increment triangleIndex through each loop.
      int indice = Tables::Triangles[configIndex][edgeIndex];

      // If the current edgeIndex is -1, there are no more indices and we can exit the function.
      if (indice == -1)
        return;

      // Get the vertices for the start and end of this edge.
      glm::vec3 vert1 = pPosition + Tables::Corners[Tables::Edges[indice][0]];
      glm::vec3 vert2 = pPosition + Tables::Corners[Tables::Edges[indice][1]];

      // Get the midpoint of this edge.
      glm::vec3 vertPosition = (vert1 + vert2) / 2.0f;

      // Add to our vertices and triangles list and incremement the edgeIndex.
      m_Vertices.push_back({vertPosition});
      m_Indices.push_back(m_Vertices.size() - 1);
      triangle[p] = m_Vertices.size() - 1;
      edgeIndex++;
    }

    // NORMALS (PER FACE)
    Vertex v1, v2, v3;
    v1 = m_Vertices[triangle[0]];
    v2 = m_Vertices[triangle[1]];
    v3 = m_Vertices[triangle[2]];

    glm::vec3 normal = glm::normalize(glm::cross((v2.position - v1.position), (v3.position - v1.position)));

    m_Vertices[triangle[0]].normals = normal;
    m_Vertices[triangle[1]].normals = normal;
    m_Vertices[triangle[2]].normals = normal;

  }
}

int Marcher::GetCubeConfiguration(float *cube) {
  int configurationIndex = 0;
  for (int i = 0; i < 8; i++) {
      if (cube[i] < m_Threshold) {
      configurationIndex |= 1 << i;
    }
  }
  return configurationIndex;
}


