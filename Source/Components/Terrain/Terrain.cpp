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

// TODO: Doc
void Terrain::Create(const glm::vec2 &pSize, float pDensity) {
  mSize = pSize;

  const float uvX = 1.0f / mSize.x;
  const float uvZ = 1.0f / mSize.y;

  Perlin p;

  // Create the base vertices.
  unsigned vertex = 0;
  double yoff = 0.0;
  double zoff = 0.0;
  for (unsigned z = 0; z < mSize.y; ++z) {

    double xoff = 0.0;

    for (unsigned x = 0; x < mSize.x; ++x) {

      float xp = x * pDensity;
      float zp = z * pDensity;

      float yp = p.Noise(5, 0.6f, xoff, yoff, zoff) * 20 * pDensity;

      mVertices.push_back({{xp, yp, zp}, {z * uvZ, x * uvX},
                           {0.0f, 1.0f, 0.0f}});

      xoff += 0.01;
    }
    zoff += 0.02;
  }
  yoff += 0.001;

  // Create indices
  unsigned offset = 0;
  for (unsigned z = 0; z < mSize.y - 1; ++z) {
    unsigned Z = z * (mSize.x);
    unsigned ZN = (z + 1) * (mSize.x);
    for (unsigned x = 0; x < mSize.x - 1; ++x) {
      mIndices.push_back(Z + x); // A
      mIndices.push_back(ZN + x + 1); // C
      mIndices.push_back(ZN + x); // D
      mIndices.push_back(ZN + x + 1); // C
      mIndices.push_back(Z + x); // A
      mIndices.push_back(Z + x + 1); // B
    }
  }

  auto Index = [&](int x, int z) {
    return z * (int) (mSize.y / pDensity) + x;
  };

  // Normals
  for (int z = 0; z < mSize.y; ++z) {
    for (int x = 0; x < mSize.x; ++x) {
      int tx, tz;
      if (x == 0) tx = 1;
      if (z == 0) tz = 1;
      float hl = mVertices[Index(tx - 1, tz)].position.y;
      float hr = mVertices[Index(tx + 1, tz)].position.y;
      float hd = mVertices[Index(tx, tz + 1)].position.y;
      float hu = mVertices[Index(tx, tz - 1)].position.y;
      glm::vec3 n = glm::vec3(hl - hr, 2.0f, hd - hu);
      mVertices[z * mSize.y + x].normals = glm::normalize(n);
    }
  }
}
