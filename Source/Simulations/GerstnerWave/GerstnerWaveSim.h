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

class GerstnerWaveSim : public Simulation {

 private:
  glm::vec4 mWave0 = glm::vec4(0.09f, 0.71f, 0.06f, 85.0f);
  glm::vec4 mWave1 = glm::vec4(-0.01f, 0.45f, 0.03f, 30.0f);
  glm::vec4 mWave2 = glm::vec4(0.18f, 0.32f, 0.06f, 40.0f);

 public:
  ~GerstnerWaveSim() override {};
  void OnCreate() override;
  void OnUpdate() override {};
  void OnFixedUpdate(const double &pStep) override {};
  void OnDraw(Shader *pShader) override;
  void OnDestroy() override {};
  void OnGUI() override;

};
