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
#include "Simulations/GerstnerWave/GerstnerWaveSim.h"
#include "Simulations/PerlinTerrain/PerlinTerrainSim.h"
#include "Simulations/MarchingCubes/MarchingCubesSim.h"
#include "Simulations/RayMarching/RayMarchingSim.h"

Application *Application::Instance = nullptr;

/**
 * Handles the creation of application components.
 */
void Application::Create() {

  Instance = this;

  // Clock -------------------------------------------------------------------------------------------------------------
  if (!mClock.Init()) {
    throw new std::exception;
  }

  // Repository --------------------------------------------------------------------------------------------------------
  mRepository.Create();

  // Renderer ----------------------------------------------------------------------------------------------------------
  Renderer::Access()->Create();

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

  while (mWindow.WindowActive()) {
    mClock.Update();
    mWindow.ProcessInput();

    mSimulation->OnUpdate();

    for (int i = 0; mClock.ShouldProceedWithSimulationStep(i); ++i) {
      mSimulation->OnFixedUpdate(mClock.GetIntervalWhileDecrementingAccumulate());
    }

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
    if (ImGui::Button("2. Perlin Terrain")) { SelectSimulation<PerlinTerrainSim>(); }
    if (ImGui::Button("3. Marching Cubes Terrain")) { SelectSimulation<MarchingCubesSim>(); }
    if (ImGui::Button("4. Gerstner Waves")) { SelectSimulation<GerstnerWaveSim>(); }
	if (ImGui::Button("5. Ray Marching")) { SelectSimulation<RayMarchingSim>(); }
  }

  ImGui::End();
}