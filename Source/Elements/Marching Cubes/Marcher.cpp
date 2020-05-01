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
#include "System/GUI/GUILayer.h"

Marcher::Marcher(const glm::vec2 &pDimensions)
    : m_Dimensions(pDimensions) {
}

void Marcher::March() {

  m_Data.clear();
  m_Vertices.clear();
  m_Indices.clear();

  // Generate the data
  for (int z = 0; z < m_Dimensions.x + 1; ++z) {
    for (int y = 0; y < m_Dimensions.y + 1; ++y) {
      for (int x = 0; x < m_Dimensions.x + 1; ++x) {
        float height = m_Amplitude * (float) m_Perlin.Noise(
            m_Octaves, m_Persistence,
            x / m_Frequency * m_FrequencyScale.x + m_Scale.x,
            y / m_Frequency * m_FrequencyScale.y + m_Scale.y,
            z / m_Frequency * m_FrequencyScale.z + m_Scale.z) + m_Surface;
        m_Data.push_back((float) y - height);
      }
    }
  }

  // Loop through each segment in our chunk.
  for (int z = 0; z < m_Dimensions.x; ++z) {
    for (int y = 0; y < m_Dimensions.y; ++y) {
      for (int x = 0; x < m_Dimensions.x; ++x) {

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
      // Get the current index.
      int indice = Tables::Triangles[configIndex][edgeIndex];

      // If the current edgeIndex is -1, there are no more indices and we can exit the function.
      if (indice == -1)
        return;

      // Get the vertices for the start and end of this edge.
      glm::vec3 vert1 = pPosition + Tables::Corners[Tables::Edges[indice][0]];
      glm::vec3 vert2 = pPosition + Tables::Corners[Tables::Edges[indice][1]];

      glm::vec3 vertPosition;
      if (m_Smoothing) {
        // Get the terrain values at either end of our current edge from the cube array created above.
        float vert1Sample = pCube[Tables::Edges[indice][0]];
        float vert2Sample = pCube[Tables::Edges[indice][1]];

        // Calculate the difference between the terrain values.
        float difference = vert2Sample - vert1Sample;

        // If the difference is 0, then the terrain passes through the middle.
        if (difference == 0)
          difference = m_Threshold;
        else
          difference = (m_Threshold - vert1Sample) / difference;

        // Calculate the point along the edge that passes through.
        vertPosition = vert1 + ((vert2 - vert1) * difference);
      } else {
        // Get the midpoint of this edge.
        vertPosition = (vert1 + vert2) / 2.0f;
      }

//      // Add to our vertices and triangles list and incremement the edgeIndex.
//      m_Vertices.push_back({vertPosition});
//      m_Indices.push_back(m_Vertices.size() - 1);
//      triangle[p] = m_Vertices.size() - 1;

      // Add to our vertices and triangles list and incremement the edgeIndex.
      if (m_FlatShading) {
        m_Vertices.push_back({vertPosition});
        m_Indices.push_back(m_Vertices.size() - 1);
        triangle[p] = m_Vertices.size() - 1;
      } else {
        m_Indices.push_back(VertForIndice(vertPosition));
        triangle[p] = m_Indices.back();
      }

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

int Marcher::VertForIndice(glm::vec3 vert) {

  // Loop through all the vertices currently in the vertices list.
  for (int i = 0; i < m_Vertices.size(); i++) {

    // If we find a vert that matches ours, then simply return this index.
    if (m_Vertices[i].position == vert)
      return i;
  }

  // If we didn't find a match, add this vert to the list and return last index.
  m_Vertices.push_back({vert});
  return m_Vertices.size() - 1;

}

int Marcher::GetCubeConfiguration(float *cube) {
  int configurationIndex = 0;
  for (int i = 0; i < 8; i++) {
    if (cube[i] > m_Threshold) {
      configurationIndex |= 1 << i;
    }
  }
  return configurationIndex;
}

void Marcher::March(int pConfigIndex) {
  m_Data.clear();
  m_Vertices.clear();
  m_Indices.clear();

  // If the configuration of this cube is 0 or 255 (completely inside the terrain or completely outside of it) we don't need to do anything.
  if (pConfigIndex == 0 || pConfigIndex == 255)
    return;

  // Loop through the triangles. There are never more than 5 triangles to a cube and only three vertices to a triangle.
  int edgeIndex = 0;
  for (int i = 0; i < 5; i++) {

    // TRIANGLE
    int triangle[3];
    for (int p = 0; p < 3; p++) {
      // Get the current indice. We increment triangleIndex through each loop.
      int indice = Tables::Triangles[pConfigIndex][edgeIndex];

      // If the current edgeIndex is -1, there are no more indices and we can exit the function.
      if (indice == -1)
        return;

      // Get the vertices for the start and end of this edge.
      glm::vec3 vert1 = Tables::Corners[Tables::Edges[indice][0]];
      glm::vec3 vert2 = Tables::Corners[Tables::Edges[indice][1]];

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


void Marcher::OnGUI() {

  ImGui::Checkbox("Smoothing?", &m_Smoothing);
  ImGui::Checkbox("Flat Shading?", &m_FlatShading);

  ImGui::DragFloat("Threshold", &m_Threshold, 0.01f, -1.0f, 1.0f);
  ImGui::DragInt("Octaves", &m_Octaves, 1, 1, 10);
  ImGui::DragFloat("Persistence", &m_Persistence, 0.01f, 0.01f, 3.0f);

  ImGui::DragFloat("Frequency", &m_Frequency, 0.1f, -128.0f, 128.0f);
  ImGui::DragFloat("Amplitude", &m_Amplitude, 0.1f, -128.0f, 128.0f);
  ImGui::DragFloat("Surface", &m_Surface, 1.0f, 0.0f, 12.0f);

  ImGui::DragFloat3("Frequency Scale", &m_FrequencyScale.x, 0.01f, 0.01f, 1.5f);
  ImGui::DragFloat3("Scale", &m_Scale.x, 0.001f, 0.001f, 3.0f);
}


