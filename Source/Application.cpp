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

#include "Application.h"
#include "Simulations/SimpleGeometry/SimpleGeometrySim.h"

/**
 * Handles the creation of application components.
 */
void Application::Create() {
  // Repository --------------------------------------------------------------------------------------------------------
  mRepository.Create();

  // Window ------------------------------------------------------------------------------------------------------------
  mGui.Create(mWindow.GetWindow());

  // Simulation --------------------------------------------------------------------------------------------------------
  SelectSimulation<SimpleGeometrySim>();

  // GUI ---------------------------------------------------------------------------------------------------------------
  mGui.AddElement([this]() { OnGUI(); });
}

/**
 * Used to tear-down application components.
 */
void Application::Destroy() {
  mSimulation->OnDestroy();
  // Repository --------------------------------------------------------------------------------------------------------
  mRepository.Destroy();
}

/**
 * Used to start and control the application's lifecycle.
 */
void Application::Run() {
  Create();
  Renderer *renderer = Renderer::Access();

  while (mWindow.WindowActive()) {
    mWindow.ProcessInput();
    mSimulation->OnUpdate();
    Renderer::Begin();
    Renderer::Draw();
    mGui.Render();
    Renderer::End();
  }
  Destroy();
}

/**
 * Used to dictate what is shown on the GUI layer.
 */
void Application::OnGUI() {

  Renderer::OnGUI();
  mRepository.OnGUI();

  // -------------------------------------------------------------------------------------------------------------------
  ImGui::Begin("Simulation");
  {
    mSimulation->OnGUI();
  }
  ImGui::End();

  // -------------------------------------------------------------------------------------------------------------------
  ImGui::Begin("Simulation Chooser");
  {
    if (ImGui::Button("1. Simple Geometry")) { SelectSimulation<SimpleGeometrySim>(); }
  }

  ImGui::End();
}