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

class Camera {
 protected:
  glm::vec3 position{0.0f, 0.0f, 3.0f}; /**< Camera position. */
  glm::vec3 front{0.0f, 0.0f, -1.0f}; /**< Camera front direction. */
  glm::vec3 right; /**< Camera right direction. */
  glm::vec3 up{0.0f, 1.0f, 0.0f};  /**< Camera up direction. */
  glm::vec3 worldUp{0.0f, 1.0f, 0.0f}; /**< World up direction. */

  glm::mat4 projection_view;
  glm::mat4 projection;
  glm::mat4 view;

  glm::vec3 rotation{0.0f, -90.0f, 0.0f}; /**< Rotations in degrees X: Pitch, Y: Yaw, Z: Roll */

  float speed = 0.5f; /**< Camera movement speed. */
  float sensitivity = 0.3f; /**< Camera rotational sensitivity. */

 public:
  Camera() {};

  virtual ~Camera() {};

  virtual void Update(double dt);
  virtual bool OnInput(double dt = 1.0) { return false; }

  // Matrices ----------------------------------------------------------------------------------------------------------
  inline const glm::mat4 &GetView() const { return view; }
  inline const glm::mat4 &GetProjection() const { return projection; }
  inline const glm::mat4 &GetProjectionView() const { return projection_view; }
  virtual void UpdateProjectionView() {};

  // Position ----------------------------------------------------------------------------------------------------------
  inline const glm::vec3 &GetPosition() const { return position; }
  inline glm::vec3 &GetPosition() { return position; }
  inline void SetPosition(float to) { position = glm::vec3(to); }
  inline void SetPosition(const glm::vec3 &to) { position = to; }
  inline void SetAndUpdatePosition(const glm::vec3 &to) { position = to; UpdateProjectionView(); }
  inline void AddPosition(float value) { position += (value * speed); }
  inline void AddPosition(const glm::vec3 &values) { position += (values * speed); }

  // Rotation ----------------------------------------------------------------------------------------------------------
  inline const glm::vec3 &GetRotation() const { return rotation; }
  inline glm::vec3 &GetRotation() { return rotation; }
  void SetRotation(const glm::vec3 &values);
  void AddRotation(const glm::vec3 &values);
  void AddAndUpdateRotation(const glm::vec3 &values);

  // Other -------------------------------------------------------------------------------------------------------------
  inline const glm::vec3 &GetFront() const { return front; }
  inline const glm::vec3 &GetUp() const { return up; }
};
