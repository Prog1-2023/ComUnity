#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

void computeMatricesFromInputs(GLFWwindow* _window = nullptr);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

#endif