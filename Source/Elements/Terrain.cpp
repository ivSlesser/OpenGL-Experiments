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


#include "Terrain.h"

#include "Math/Random/Perlin.h"

Terrain::Terrain(glm::vec4 color, const glm::vec3 &pos, const glm::vec2 &size, float resolution) {

  mSize = size;

  const float uvX = 1.0f / size.x;
  const float uvZ = 1.0f / size.y;

  Perlin p;

  // Create the base vertices.
  unsigned vertex = 0;
  double yoff = 0.0;
  double zoff = 0.0;
  for (unsigned z = 0; z < size.y; ++z) {

    double xoff = 0.0;

    for (unsigned x = 0; x < size.x; ++x) {

      float xp = pos.x + x * resolution;
      float zp = pos.z + z * resolution;

      float yp = pos.y + p.Noise(5, 0.6f, xoff, yoff, zoff) * 20 * resolution;

      vertices.push_back({{xp, yp, zp}, color, {z * uvZ, x * uvX},
                          {0.0f, 1.0f, 0.0f}});

      xoff += 0.01;
    }
    zoff += 0.02;
  }
  yoff += 0.001;

  // Create indices
  unsigned offset = 0;
  for (unsigned z = 0; z < size.y - 1; ++z) {
    unsigned Z = z * (size.x);
    unsigned ZN = (z + 1) * (size.x);
    for (unsigned x = 0; x < size.x - 1; ++x) {
      indices.push_back(Z + x); // A
      indices.push_back(ZN + x + 1); // C
      indices.push_back(ZN + x); // D
      indices.push_back(ZN + x + 1); // C
      indices.push_back(Z + x); // A
      indices.push_back(Z + x + 1); // B
    }
  }

  auto Index = [&](int x, int z) {
    return z * (int) (size.y / resolution) + x;
  };

  // Normals
  for (int z = 0; z < size.y; ++z) {
    for (int x = 0; x < size.x; ++x) {
      int tx, tz;
      if (x == 0) tx = 1;
      if (z == 0) tz = 1;
      float hl = vertices[Index(tx - 1, tz)].position.y;
      float hr = vertices[Index(tx + 1, tz)].position.y;
      float hd = vertices[Index(tx, tz + 1)].position.y;
      float hu = vertices[Index(tx, tz - 1)].position.y;
      glm::vec3 n = glm::vec3(hl - hr, 2.0f, hd - hu);
      vertices[z * size.y + x].normals = glm::normalize(n);
    }
  }

}

glm::vec3 Terrain::sampleAtPoint(const glm::vec2 &pPoint) {
  // TODO: Return an approximate height value for a supplied point.
  int x = (int) pPoint.x;
  int z = (int) pPoint.y;
  int index = mSize.y * z + x;
  return vertices[index].position;
}
