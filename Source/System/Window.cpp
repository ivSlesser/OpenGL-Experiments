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


#include "Window.h"

#include "OpenGL/Renderer.h"
#include "Graphics/Camera/PerspectiveCamera.h"

GLFWwindow *Window::s_Window = nullptr;
Window *Window::s_Instance = nullptr;

Window::Window() {

  Window::s_Instance = this;

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.major);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.minor);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//  glfwWindowHint(GLFW_SAMPLES, 0);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  window = glfwCreateWindow(config.width, config.height, config.title, NULL, NULL);
  if (window == NULL) {
	std::cout << "Failed to create GLFW window" << std::endl;
	glfwTerminate();
	std::abort();
  }
  glfwMakeContextCurrent(window);

  glfwSwapInterval( 0 );

  glfwSetFramebufferSizeCallback(window, Window::OnResize);
  glfwSetCursorPosCallback(window, Window::OnMouseMove);
  glfwSetMouseButtonCallback(window, Window::OnMouseButton);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
	std::cout << "Failed to initialize GLAD" << std::endl;
	std::abort();
  }

  glEnable(GL_DEPTH_TEST);

  Window::s_Window = window;
}

Window::~Window() {
  glfwTerminate();
}

void Window::Begin() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::End() {
  glfwSwapBuffers(window);
}

void Window::ProcessInput() {
  glfwPollEvents();

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	glfwSetWindowShouldClose(window, true);
}

void Window::OnResize(GLFWwindow *window, int width, int height) {
  Window::s_Instance->config.width = width;
  Window::s_Instance->config.height = height;

  if (!Window::s_Instance->config.usingFramebuffer) {
    glViewport(0, 0, width, height);
  }
}

void Window::OnMouseMove(GLFWwindow *window, double xpos, double ypos) {
  static float prevX = 0.0f;
  static float prevY = 0.0f;

  static bool firstMouse = true;
  if (s_Instance->is_right_mouse_held) {
	if (firstMouse) {
	  prevX = xpos;
	  prevY = ypos;
	  firstMouse = false;
	}

	float xoffset = xpos - prevX;
	float yoffset = prevY - ypos;

	prevX = xpos;
	prevY = ypos;

	Renderer::GetCamera().AddAndUpdateRotation(glm::vec3(yoffset, xoffset, 0.0f));
  } else {
	firstMouse = true;
  }
}

void Window::OnMouseButton(GLFWwindow *m, int button, int action, int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT) {
	if (action == GLFW_PRESS)
	  s_Instance->is_left_mouse_held = true;
	else if (action == GLFW_RELEASE)
	  s_Instance->is_left_mouse_held = false;
  }

  if (button == GLFW_MOUSE_BUTTON_RIGHT) {
	if (action == GLFW_PRESS)
	  s_Instance->is_right_mouse_held = true;
	else if (action == GLFW_RELEASE)
	  s_Instance->is_right_mouse_held = false;
  }
}

