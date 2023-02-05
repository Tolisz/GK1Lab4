#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera.h"

#include <ostream>

class OCamera
{
public:

	OCamera(const glm::vec3& position);
	OCamera(glm::vec3 position, glm::vec3 front, glm::vec3 up, glm::vec3 right, glm::vec3 worldUp, float yaw, float pitch);

	void processMouse(GLFWwindow* window, double xposIn, double yposIn);
	void processKeyboard(GLFWwindow* window/*, int key, int scancode, int action, int mods)*/);

	void setPosition(glm::vec3 camera_position);
	void setTarget(glm::vec3 target_position);
	glm::mat4 GetViewMatrix();
	glm::vec3 GetPosition();
	glm::vec3 GetTarget();
	glm::vec3 GetFront();

	friend std::ostream& operator<<(std::ostream& out, const OCamera& c);

public:

	bool isMovable = false;
	bool hasTarget = false;

private:

	Camera m_camera;
};