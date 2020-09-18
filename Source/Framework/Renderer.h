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

#define DEBUG_ONLY(x)   x;

#define CHECK_GL_ERROR(x)   Renderer::ClearGLError();     \
                            x;                            \
                            Renderer::CheckGLError(#x);

#include "Common.h"

#include "System/Window.h"

#include "./Components/Camera/PerspectiveCamera.h"

#include "Framework/Components/Transform.h"
#include "Framework/GL/Texture.h"
#include "Framework/GL/VertexArray.h"
#include "Framework/GL/VertexBuffer.h"
#include "Framework/GL/IndexBuffer.h"
#include "Framework/GL/FrameBuffer.h"
#include "Framework/GL/UniformBuffer.h"
#include "Framework/GL/Shader.h"

struct GeneralUniformBuffer : public UniformBufferContents {
  glm::vec3 SkyColor{0.474f};            // Clear color for the buffer swap routine.
  float AmbientStrength{0.32f};                 // Ambient lighting strength
  glm::vec3 SunColor{1.0f};              // Sun (global light) color
  float SpecularStrength{0.5f};                 // Specular highlight strength
  glm::vec3 SunPosition{500.0f};         // Sun (global light position
  float Time;                                   // Time elapsed
  float DeltaTime;                              // Delta Time
};

struct CameraUniformBuffer : public UniformBufferContents {
  glm::mat4 View{1.0f};                      // View Matrix
  glm::mat4 Projection{1.0f};                // Projection Matrix
  glm::mat4 ViewProjection{1.0f};            // View * Projection Matrix
  glm::vec3 Position;                           // Camera Position
  float Near;                                   // Camera Near Plane
  glm::vec3 Front;                              // Camera Front Vector
  float Far;                                    // Camera Far Plane
  glm::vec3 Up;                                 // Camera Up Vector
};

class Renderer {

 private:
  static Renderer *s_Instance;

  // Rendering Statistics ----------------------------------------------------------------------------------------------
  struct RenderingStatistics {
	uint32_t Calls = 0;
	uint32_t Vertices = 0;
	uint32_t Indices = 0;
  } mStatistics;                              // Collected statistics for the renderer.

  // Rendering Settings ------------------------------------------------------------------------------------------------
  struct RenderingSettings {
	bool IsWireframeEnabled{false};           // Is the wire-frame mode enabled?
	bool ApplyFog{true};                      // Should apply fog effect?
	float FogDensity{0.0035f};                // How thick the fog is. Greater means lower visibility.
	float FogGradient{5.0f};                  // How quickly visibility decreases. Greater means smaller view distance.

  } mSettings;                                // Rendering settings

  // Lighting Settings -------------------------------------------------------------------------------------------------
  struct LightingSettings {
	glm::vec3 SkyColor{0.474f};       // Clear color for the buffer swap routine.
	glm::vec3 SunColor{1.0f};         // Sun (global light) color
	glm::vec3 SunPosition{1000.0f};   // Sun (global light position
	float AmbientStrength{0.2f};              // Ambient lighting strength
	float SpecularStrength{0.5f};             // Specular highlight strength

  } mLightSettings;                           // Lighting settings

  // Post Processing Settings ------------------------------------------------------------------------------------------
  struct PostProcessingSettings {
	bool ApplyGreyscale{false};               // Should apply greyscale effect?
	bool ApplyInvert{false};                  // Should apply inversion effect?
	float ContrastStrength{1.0f};             // Strength of contrast effect

  } mPPSettings;                              // Post processing settings.

  // Uniform Buffers ---------------------------------------------------------------------------------------------------
  struct UniformBuffers {
	UniformBuffer GeneralUBO;                 // General Uniform Buffer
	UniformBuffer CameraUBO;                  // Camera Uniform Buffer

  } mUniformBuffers;                          // Post processing settings.

  // Variables ---------------------------------------------------------------------------------------------------------
  uint32_t mPostProcessingShaderID{0};        // Post processing shader ID
  uint32_t mPostActionShaderID{0};            // Post draw action shader ID

  VertexArray mScreenVAO;                     // Output VAO for Post processing rectangle.
  VertexBuffer mScreenVBO;                    // Output VBO for Post processing rectangle.
  IndexBuffer mScreenIBO;                     // Output IBO for Post processing rectangle.
  FrameBuffer mPrimaryFBO;                    // Primary Framebuffer for rendering.

  PerspectiveCamera camera;                   // Camera (Will refactor into repo)


  // Texture Related ---------------------------------------------------------------------------------------------------

  // TODO: Add Textures To Repo
//  Texture cat_texture = Texture("Resources/Textures/cat.jpg");
//  Texture ref_texture = Texture("Resources/Textures/Debug.png");

  // -------------------------------------------------------------------------------------------------------------------

 public:
  static Renderer *Access();

  void Create();
  static void Begin();
  static void End();
  static void Draw();
  static void OnGUI();

  static void RegisterUniformBuffersToShader(uint32_t pShaderID);
  static void ToggleWireframeRendering();
  static void SetWireframeRendering(bool pTo);

  inline static Camera &GetCamera() { return Renderer::Access()->camera; }

  /**
   * Utility function to clear all OpenGL errors.
   */
  static void ClearGLError() {
	unsigned errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR) {
	}
  }

  /**
   * Utility function to check if there is an error flaged by the
   * OpenGL API.
   *
   * @param msg             [Optional] Message to prepend to error check output.
   */
  static void CheckGLError(std::string msg = "") {
	auto res = glGetError();
	if (res != 0) {
	  std::cout << msg << " -> " << res << std::endl;
	}
  }

 private:
  Renderer();
};
