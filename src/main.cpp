#include "util.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow*, int width, int height)
{
  glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window)
{
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void setup_debug(bool enable)
{
  glDebugMessageCallbackKHR(enable ? gl_debug_logger : nullptr, stderr);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_KHR);
  if (GL_NO_ERROR != glGetError())
    std::cerr << "Unable to set synchronous debug output\n";
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

#ifndef NDEBUG
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

  constexpr auto INIT_WIDTH = 800u;
  constexpr auto INIT_HEIGHT = 600u;
  GLFWwindow* window = glfwCreateWindow(INIT_WIDTH, INIT_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
#ifndef NDEBUG
  if (GLAD_GL_KHR_debug)
  {
    setup_debug(true);
  }
#endif
  glViewport(0, 0, INIT_WIDTH, INIT_HEIGHT);
  glClearColor(0.188f, 0.349f, 0.506f, 1.0f);

  while (!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT);
    process_input(window);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}
