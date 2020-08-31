// MIT License
//
// Copyright (c) 2020 Ian Vincent Slesser
//
// Permission is hereby granted, free ofcharge, to any person obtaining a copy
// ofthis software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies ofthe Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions ofthe Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#include "Shapes3D.h"

// Cube ----------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

std::vector<Vertex> Cube::Vertices() {
  return {
      {{-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}, {-0.5f, -0.5f, -0.5f}},
      {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {0.5f, -0.5f, -0.5f}},
      {{1.0f, 1.0f, -1.0f}, {0.0f, 1.0f}, {0.5f, 0.5f, -0.5f}},
      {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f}, {-0.5f, 0.5f, -0.5f}},

      {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f}, {-0.5f, -0.5f, 0.5f}},
      {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f}, {0.5f, -0.5f, 0.5f}},
      {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.5f, 0.5f, 0.5f}},
      {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {-0.5f, 0.5f, 0.5f}}
  };
}

std::vector<uint32_t> Cube::Indices(uint32_t pOffset) {
  return {
      0 + pOffset, 1 + pOffset, 3 + pOffset, 3 + pOffset, 1 + pOffset, 2 + pOffset,
      1 + pOffset, 5 + pOffset, 2 + pOffset, 2 + pOffset, 5 + pOffset, 6 + pOffset,
      5 + pOffset, 4 + pOffset, 6 + pOffset, 6 + pOffset, 4 + pOffset, 7 + pOffset,
      4 + pOffset, 0 + pOffset, 7 + pOffset, 7 + pOffset, 0 + pOffset, 3 + pOffset,
      3 + pOffset, 2 + pOffset, 7 + pOffset, 7 + pOffset, 2 + pOffset, 6 + pOffset,
      4 + pOffset, 5 + pOffset, 0 + pOffset, 0 + pOffset, 5 + pOffset, 1 + pOffset
  };
}

// CubeFlat ------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

std::vector<Vertex> CubeFlat::Vertices() {
  std::vector<Vertex> vertices(36);

  // TODO: Get Rid OfDuplicate Vertices In Each Face
  // TODO: Fix, see wireframe mode!
  return {
      // Front
      {{-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}}, // BL
      {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}}, // TL
      {{1.0f, 1.0f, -1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}}, // TR
      {{1.0f, 1.0f, -1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}}, // TR
      {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}}, // BR
      {{-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}}, // BL

      // Back
      {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}, // BL
      {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}, // BR
      {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}, // TR
      {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}, // TR
      {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}, // TL
      {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}, // BL

      // Right
      {{-1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}}, // TR
      {{-1.0f, 1.0f, -1.0f}, {0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}}, // TL
      {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}}, // BL
      {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}}, // BL
      {{-1.0f, -1.0f, 1.0f}, {1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}}, // BR
      {{-1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}}, // TR

      // Left
      {{1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}}, // TL
      {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}}, // TR
      {{1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}}, // BR
      {{1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}}, // BR
      {{1.0f, -1.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}}, // BL
      {{1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}}, // TL

      // Bottom
      {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}}, // TR
      {{1.0f, -1.0f, -1.0f}, {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}, // BL
      {{1.0f, -1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}, // BR
      {{1.0f, -1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}, // BR
      {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}}, // TR
      {{-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}}, // TL

      // Top
      {{-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}}, // BR
      {{1.0f, 1.0f, -1.0f}, {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}}, // BL
      {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}}, // TL
      {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}}, // TL
      {{-1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}}, // TR
      {{-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}} // BR
  };
}
std::vector<uint32_t> CubeFlat::Indices(uint32_t pOffset) {
  return {};
}

// Plane ---------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

Plane::Plane(const glm::vec2 &pSize, float pResolution) {
  const float uvX = 1.0f / (pSize.x - 1);
  const float uvZ = 1.0f / (pSize.y - 1);

  // Create the base vertices.
  unsigned vertex = 0;
  for (unsigned x = 0; x < pSize.x; ++x) {
    for (unsigned z = 0; z < pSize.y; ++z) {
      float xp = x * pResolution;
      float zp = z * pResolution;
      mVertices.push_back({{xp, 0.0f, zp}, {z * uvZ, x * uvX}, {0.0f, 1.0f, 0.0f}});
    }
  }

  // Create indices
  unsigned offset = 0;
  for (unsigned z = 0; z < pSize.y - 1; ++z) {
    unsigned Z = z * (pSize.x);
    unsigned ZN = (z + 1) * (pSize.x);
    for (unsigned x = 0; x < pSize.x - 1; ++x) {
      mIndices.push_back(Z + x); // A
      mIndices.push_back(ZN + x + 1); // C
      mIndices.push_back(ZN + x); // D

      mIndices.push_back(ZN + x + 1); // C
      mIndices.push_back(Z + x); // A
      mIndices.push_back(Z + x + 1); // B
    }
  }
}
