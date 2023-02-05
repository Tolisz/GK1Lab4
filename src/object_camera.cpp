#include "object_camera.h"

#include <iostream>

#include "global.h"
#include <iomanip>


OCamera::OCamera(const glm::vec3& position):
    m_camera(position)
{

}

OCamera::OCamera(glm::vec3 position, glm::vec3 front, glm::vec3 up, glm::vec3 right, glm::vec3 worldUp, float yaw, float pitch):
    m_camera(position, front, up, right, worldUp, yaw, pitch)
{

}

glm::mat4 OCamera::GetViewMatrix()
{
    return m_camera.GetViewMatrix();
}

void OCamera::setTarget(glm::vec3 target_position)
{
    m_camera.setTarget(target_position);
}

void OCamera::setPosition(glm::vec3 camera_position)
{
    m_camera.setPosition(camera_position);
}

glm::vec3 OCamera::GetPosition()
{
    return m_camera.GetPosition();
}

glm::vec3 OCamera::GetTarget()
{
    return m_camera.GetTarget();
}

glm::vec3 OCamera::GetFront()
{
    return m_camera.Front;
}

void OCamera::processMouse(GLFWwindow* window, double xposIn, double yposIn)
{
    if (!isMovable)
        return;

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
    if (!isMovable)
        return;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_camera.ProcessKeyboard(FORWARD, G::deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_camera.ProcessKeyboard(BACKWARD, G::deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_camera.ProcessKeyboard(LEFT, G::deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_camera.ProcessKeyboard(RIGHT, G::deltaTime);
}

std::ostream& operator<<(std::ostream& out, const OCamera& c)
{
    auto wvec = [&out](glm::vec3 v) -> std::ostream&
    { 
        out << "[" << v.x << ", " << v.y << ", " << v.z << "]";
        return out;
    };

    out << "------------------------ Camera ------------------------ " << std::endl;

    out << std::setw(20) << std::left << "Front = ";        wvec(c.m_camera.Front) << std::endl;
    out << std::setw(20) << std::left << "Up = ";           wvec(c.m_camera.Up) << std::endl;
    out << std::setw(20) << std::left << "Right = ";        wvec(c.m_camera.Right) << std::endl;
    out << std::setw(20) << std::left << "Position = ";     wvec(c.m_camera.Position) << std::endl;
    out << std::setw(20) << std::left << "WorldUp = ";      wvec(c.m_camera.WorldUp) << std::endl;

    out << std::setw(20) << std::left << "Pitch = " << c.m_camera.Pitch << std::endl;
    out << std::setw(20) << std::left << "Yaw = " << c.m_camera.Yaw << std::endl;

    return out;
}