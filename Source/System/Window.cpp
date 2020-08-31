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

#include "Framework/Renderer.h"
#include "Framework/Components/Camera/PerspectiveCamera.h"

GLFWwindow *Window::sWindow = nullptr;
Window *Window::sInstance = nullptr;

Window::Window() {

  Window::sInstance = this;

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mConfig.major);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, mConfig.minor);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//  glfwWindowHint(GLFW_SAMPLES, 0);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  mWindow = glfwCreateWindow(mConfig.width, mConfig.height, mConfig.title, NULL, NULL);
  if (mWindow == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    std::abort();
  }
  glfwMakeContextCurrent(mWindow);

  glfwSwapInterval(0);

  glfwSetFramebufferSizeCallback(mWindow, Window::OnResize);
  glfwSetCursorPosCallback(mWindow, Window::OnMouseMove);
  glfwSetMouseButtonCallback(mWindow, Window::OnMouseButton);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    std::abort();
  }

  glEnable(GL_DEPTH_TEST);

  Window::sWindow = mWindow;
}

Window::~Window() {
  glfwTerminate();
}

void Window::ProcessInput() {
  glfwPollEvents();

  if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(mWindow, true);
}

void Window::OnResize(GLFWwindow *window, int width, int height) {
  Window::sInstance->mConfig.width = width;
  Window::sInstance->mConfig.height = height;

  if (!Window::sInstance->mConfig.usingFramebuffer) {
    glViewport(0, 0, width, height);
  }
}

void Window::OnMouseMove(GLFWwindow *window, double xpos, double ypos) {
  static float prevX = 0.0f;
  static float prevY = 0.0f;

  static bool firstMouse = true;
  if (sInstance->mIsRightMouseHeld) {
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
      sInstance->mIsLeftMouseHeld = true;
    else if (action == GLFW_RELEASE)
      sInstance->mIsLeftMouseHeld = false;
  }

  if (button == GLFW_MOUSE_BUTTON_RIGHT) {
    if (action == GLFW_PRESS)
      sInstance->mIsRightMouseHeld = true;
    else if (action == GLFW_RELEASE)
      sInstance->mIsRightMouseHeld = false;
  }
}

