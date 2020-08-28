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

#include "System/Module.h"
#include "System/Window.h"
#include "System/GUI/GUILayer.h"
#include "Graphics/Properties/Transform.h"
#include "OpenGL/Renderer.h"

class Application {
 private:
  Window mWindow;
  GUILayer mGui;
  Module *mModule{nullptr};
  Transform mTransform;
  bool mWireframe = false;

 public:
  void Run();

 private:
  void Init();
  void ModuleSelector(std::string name);

  // Used to switch modules.
  template <typename T>
  void SwitchModule() {
	if (mModule != nullptr) {
      mModule->OnDestroy();
	  delete mModule;
	}
    mTransform = Transform();
    mModule = new T();
    mModule->OnInit(Renderer::GetCamera());
  }
};
