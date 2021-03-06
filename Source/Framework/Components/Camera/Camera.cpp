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
#include "Camera.h"

void Camera::Update(double dt) {
  if (OnInput(dt)) {
	UpdateProjectionView();
  }
}

void Camera::SetRotation(const glm::vec3 &values) {
  rotation = values;

  if (rotation.x > 89.0f) rotation.x = 89.0f;
  if (rotation.x < -89.0f) rotation.x = -89.0f;
}

void Camera::AddRotation(const glm::vec3 &values) {
  rotation += (values * sensitivity);

  if (rotation.x > 89.0f) rotation.x = 89.0f;
  if (rotation.x < -89.0f) rotation.x = -89.0f;
}

void Camera::AddAndUpdateRotation(const glm::vec3 &values) {
  rotation += (values * sensitivity);

  if (rotation.x > 89.0f) rotation.x = 89.0f;
  if (rotation.x < -89.0f) rotation.x = -89.0f;

  glm::vec3 _front;
  _front.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
  _front.y = sin(glm::radians(rotation.x));
  _front.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
  front = glm::normalize(_front);

  right = glm::normalize(glm::cross(front, worldUp));
  up = glm::normalize(glm::cross(right, front));

  UpdateProjectionView();
}
