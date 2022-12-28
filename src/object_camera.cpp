#include "object_camera.h"

#include <iostream>

#include "global.h"



OCamera::OCamera(const glm::vec3& position):
    m_camera(position)
{

}

glm::mat4 OCamera::GetViewMatrix()
{
    return m_camera.GetViewMatrix();
}

void OCamera::processMouse(GLFWwindow* window, double xposIn, double yposIn)
{
    static float lastX = 800 / 2.0f;
    static float lastY = 600 / 2.0f;
    static bool firstMouse = true;

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    m_camera.ProcessMouseMovement(xoffset, yoffset);
}

void OCamera::processKeyboard(GLFWwindow* window/*, int key, int scancode, int action, int mods*/)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_camera.ProcessKeyboard(FORWARD, G::deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_camera.ProcessKeyboard(BACKWARD, G::deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_camera.ProcessKeyboard(LEFT, G::deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_camera.ProcessKeyboard(RIGHT, G::deltaTime);
}