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


#pragma once

#include "Common.h"
#include "Framework/Geometry/Shapes3D.h"
#include "Framework/Geometry/Vertex.h"
#include "Math/Random/Perlin.h"

// TODO: Make threaded!

class Marcher : public Plane {

 private:
  Perlin mPerlin;

  std::vector<float> mData;
  glm::vec2 mDimensions = glm::vec2(32.0f);
  float mDensity = 1.0f;

  float mThreshold = 0.5f;
  bool mSmoothing = false;
  bool mFlatShading = false;

  int mOctaves = 3;
  float mPersistence = 0.6f;
  float mFrequency = 16.0f;
  float mAmplitude = 4.0f;
  float mSurface = 6.0f;

  glm::vec3 mFrequencyScale = glm::vec3(1.5f, 1.5f, 1.5f);
  glm::vec3 mScale = glm::vec3(0.001f, 0.001f, 0.001f);

 public:
  Marcher() {};

  void Create(const glm::vec2 &pDimensions, float pDensity) override;
  void Create();

  void March();
  void March(int pConfigIndex);

  int VertForIndice(glm::vec3 vert);
  void OnGUI();

 private:
  void CellOperation(float pCube[], const glm::vec3 &pPosition);
  int GetCubeConfiguration(float cube[]);

  // Indexes
  inline int I2D(int x, int z) { return x + z * mDimensions.x + 1; };
  inline int I3D(int x, int y, int z) {
    return z * (mDimensions.y + 1) * (mDimensions.x + 1) + y * (mDimensions.x + 1) + x;
  }

};
