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
#include "../../Framework/Simulation.h"

class SimpleGeometrySim : public Simulation {

 private:
  enum Selection {
    TRIANGLE = 0,
    RECTANGLE,
    POLYGON,
    CUBE,
    CUBEFLAT,
    PLANE,
    MODEL,
  };

  Selection mSelection{Selection::TRIANGLE};          // Currently selected geometry component
  uint32_t mNumSidesPolygon{5};                       // Number of sides of the polygon

 public:
  void OnCreate() override;
  void OnUpdate() override;
  void OnDestroy() override;
  void OnGUI() override;

 private:
  void SetSelection(Selection pSelection);

  // Shape Creation
  void CreateTriangle();
  void CreateRectangle();
  void CreatePolygon(uint32_t pSides);
  void CreateCube();
  void CreateFlatCube();
  void CreatePlane();
  void CreateModel();

  // Shape Specific
  void ChangePolygonSides(uint32_t pSides);
};
