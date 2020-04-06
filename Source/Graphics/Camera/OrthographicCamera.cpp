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


#include "OrthographicCamera.h"
#include "System/Window.h"


bool OrthographicCamera::OnInput(double dt) {
  bool needRecalc = false;

  if (glfwGetKey(Window::s_Window, GLFW_KEY_W) == GLFW_PRESS) {
	AddPosition(-up * (float) dt);
	needRecalc = true;
  } else if (glfwGetKey(Window::s_Window, GLFW_KEY_S) == GLFW_PRESS) {
	AddPosition(up * (float) dt);
	needRecalc = true;
  }

  if (glfwGetKey(Window::s_Window, GLFW_KEY_A) == GLFW_PRESS) {
	AddPosition(-glm::normalize(glm::cross(front, up)) * (float) dt);
	needRecalc = true;
  } else if (glfwGetKey(Window::s_Window, GLFW_KEY_D) == GLFW_PRESS) {
	AddPosition(glm::normalize(glm::cross(front, up)) * (float) dt);
	needRecalc = true;
  }

  return needRecalc;
}

void OrthographicCamera::UpdateProjectionView() {
  const glm::vec2 &dimensions = glm::vec2(800.0f, 600.0f);
  float aspect = dimensions.x / dimensions.y;

  // TODO: Zoom
  float zoom = 1.0f;

  glm::mat4 view = glm::lookAt(position, position + front, up);
  glm::mat4 projection = glm::ortho(-aspect * zoom, aspect * zoom, -zoom, zoom, -1.0f, 1.0f);
  projection_view = projection * view;
}
