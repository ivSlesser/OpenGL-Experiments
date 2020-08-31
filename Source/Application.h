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

#include "Framework/Repository.h"
#include "Framework/Simulation.h"

#include "System/Window.h"
#include "System/GUI/GUILayer.h"
#include "Framework/Components/Transform.h"
#include "Framework/Renderer.h"

class Application {

 private:
  Repository mRepository;
  Window mWindow;
  GUILayer mGui;
  Simulation *mSimulation{nullptr};
  bool mWireframe = false;

 public:
  void Run();

 private:
  void Create();
  void Destroy();

  void OnGUI();

  // Used to switch simulations.
  template<typename T>
  void SelectSimulation() {
    if (mSimulation != nullptr) {
      mSimulation->OnDestroy();
      delete mSimulation;
    }
    mSimulation = new T();
    mSimulation->OnInit();
  }

 public:
  inline Repository *GetRepository() { return &mRepository; }
};
