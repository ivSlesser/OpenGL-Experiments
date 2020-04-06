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


#include "PerspectiveCamera.h"

#include "System/Window.h"

bool PerspectiveCamera::OnInput(double dt) {
  bool needRecalc = false;

  if (glfwGetKey(Window::s_Window, GLFW_KEY_W) == GLFW_PRESS)
  {
	AddPosition(front * (float)dt);
	needRecalc = true;
  }
  else if (glfwGetKey(Window::s_Window, GLFW_KEY_S) == GLFW_PRESS)
  {
	AddPosition(-front * (float)dt);
	needRecalc = true;
  }

  if (glfwGetKey(Window::s_Window, GLFW_KEY_A) == GLFW_PRESS)
  {
	AddPosition(-glm::normalize(glm::cross(front, up)) * (float)dt);
	needRecalc = true;
  }
  else if (glfwGetKey(Window::s_Window, GLFW_KEY_D) == GLFW_PRESS)
  {
	AddPosition(glm::normalize(glm::cross(front, up)) * (float)dt);
	needRecalc = true;
  }

//  if (App::Input->MouseMoved() && App::Input->Held(Mouse::MOUSE_RIGHT))
//  {
//	Vec2 offsets = App::Input->MouseOffsets();
//	AddRotation({offsets.x, offsets.y, 0.0f});
//	needRecalc = true;
//  }
//
//  if (needRecalc) {
//    glm::vec3 _front;
//    _front.x = Math::Cos(rotation.y * Math::DEG2RAD) * Math::Cos(rotation.x * Math::DEG2RAD);
//    _front.y = Math::Sin(rotation.x * Math::DEG2RAD);
//    _front.z = Math::Sin(rotation.y * Math::DEG2RAD) * Math::Cos(rotation.x * Math::DEG2RAD);
//    front = glm::normalize(_front);
//
//    right = glm::normalize(glm::cross(front, worldUp));
//    up = glm::normalize(glm::cross(right, front));
//  }

  return needRecalc;
}

void PerspectiveCamera::UpdateProjectionView() {
  float aspect = 800 / 600;
  glm::mat4 view = glm::lookAt(position, position + front, up);
  glm::mat4 projection = glm::perspective(glm::radians(fov), aspect, near, far);
  projection_view = projection * view;
}
