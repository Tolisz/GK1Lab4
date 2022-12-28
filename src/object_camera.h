#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera.h"

class OCamera
{
public:

	OCamera(const glm::vec3& position);
	
	void processMouse(GLFWwindow* window, double xposIn, double yposIn);
	void processKeyboard(GLFWwindow* window/*, int key, int scancode, int action, int mods)*/);

	glm::mat4 GetViewMatrix();

private:

	Camera m_camera;

		
};